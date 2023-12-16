<script lang="ts">
	import { get } from "svelte/store";

	import LidarStream from "../lib/LidarStream.svelte";
	import { websocket_store, websocket_url_store } from "../lib/WebsocketStore";

    export let params: {room_name?: string} = {};

    let room_name = "";
    $: {
        room_name = "";
        if (params?.room_name) {
			room_name = params.room_name;
			websocket_url_store.set(
				`ws://${location.host}/ws/room?request=create&room_name=${room_name}`,
			);
			websocket_store.subscribe((websocket: any) => {
				websocket!!.addEventListener("open", (event: any) => {
					console.log("Websocket opened");
				});

				websocket!!.addEventListener("message", (event: MessageEvent<any>) => {
					const json_data = JSON.parse(event.data);
					console.log(json_data);
				});
			});

        }
    }
	
	let message = "";
	function sendMessage() {
		const websocket = get(websocket_store);
		websocket!!.send(JSON.stringify({ data: message }));
	}
</script>

<h1>This is the Room page</h1>
<h2>Title: {room_name}</h2>

<input
	on:keydown={(key_event) => {
		if (key_event.key === "Enter") sendMessage();
	}}
	bind:value={message}
/>
<button on:click={sendMessage}>Send</button>

<h1>Hello {room_name}!</h1>

{#if $websocket_url_store !== undefined}
	<LidarStream />
{:else}
	<p>Waiting to retrieve the Websocket Url...</p>
{/if}