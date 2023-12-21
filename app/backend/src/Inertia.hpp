#ifndef INERTIA_HPP
#define INERTIA_HPP

#pragma once

#include <drogon/HttpAppFramework.h>
#include <drogon/HttpResponse.h>

#include <picosha2.h>

class Inertia
{
public:
	static drogon::HttpResponsePtr newInertiaResponse(
		const drogon::HttpRequestPtr& req,
		std::unordered_map<std::string, std::function<std::string()>>& prop_functions,
		const std::string& component,
		const std::string& url
	) {
		if (req->getHeader("X-Requested-With") != "XMLHttpRequest" || req->getHeader("X-Inertia") != "true") {
			drogon::HttpViewData http_view_data = drogon::HttpViewData{};
			http_view_data["data-page"] = std::make_any<std::string>(
				getJsonResult(
					prop_functions,
					component,
					url
				).asString()
			);
			return drogon::HttpResponse::newHttpViewResponse("inertia.html", http_view_data);
		}
		const std::string& inertia_version = req->getHeader("X-Inertia-Version");
		if (inertia_version != getAssetVersion()) {
			auto response = drogon::HttpResponse::newHttpResponse();
			response->setStatusCode(drogon::HttpStatusCode::k409Conflict);
			response->addHeader("X-Inertia-Location", url);
			return response;
		}
		const std::string& inertia_partial_component = req->getHeader("X-Inertia-Partial-Component");
		const std::string& inertia_partial_data = req->getHeader("X-Inertia-Partial-Data");
		if (inertia_partial_component != "" && inertia_partial_component == component && inertia_partial_data != "") {
			std::stringstream ss(inertia_partial_data);
			std::vector<std::string> props;
			while (ss.good())
			{
				std::string substr;
				std::getline(ss, substr, ',');
				props.push_back(substr);
			}
			auto response = drogon::HttpResponse::newHttpJsonResponse(
				getJsonResult(
					prop_functions,
					component,
					url,
					std::make_optional<std::vector<std::string>&>(props)
				)
			);
			return response;
		}
		else {
			auto response = drogon::HttpResponse::newHttpJsonResponse(getJsonResult(prop_functions, component, url));
			response->addHeader("Vary", "Accept");
			response->addHeader("X-Inertia", "true");
			return response;
		}
	}
private:
	static std::string getAssetVersion() {
		std::string src_str = drogon::app().getCustomConfig()["Version"].asString();
		std::vector<unsigned char> hash(picosha2::k_digest_size);
		picosha2::hash256(src_str.begin(), src_str.end(), hash.begin(), hash.end());
		std::string hex_str = picosha2::bytes_to_hex_string(hash.begin(), hash.end());
		return hex_str;
	}

	static Json::Value getJsonResult(
		std::unordered_map<std::string, std::function<std::string()>> prop_functions,
		const std::string& component,
		const std::string& url,
		std::optional<std::vector<std::string>&> props = std::nullopt
	) {
		Json::Value json;
		json["component"] = component;
		json["url"] = url;
		json["version"] = getAssetVersion();
		if (props.has_value()) {
			for (auto& prop : props.value()) {
				const auto prop_function_pair = prop_functions.find(prop);
				if (prop_function_pair == prop_functions.end()) {
					continue;
				}
				json["props"][prop_function_pair->first] = std::any_cast<std::string>(prop_function_pair->second());
			}
		}
		else {
			for (auto& [prop_function_name, prop_function] : prop_functions) {
				json["props"][prop_function_name] = std::any_cast<std::string>(prop_function());
			}
		}
		return json;
	}
};

#endif