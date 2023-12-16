<script lang="ts">
	async function fetchRooms() {
		const res = await fetch(`http://${location.host}/api/v1/rooms`);
		const data = await res.json();

		if (res.ok) {
			return data;
		} else {
			throw new Error(data);
		}
	}
</script>

<h1>Hello world!</h1>
<p>
	Visit the <a href="https://svelte.dev/tutorial">Svelte tutorial</a> to learn
	how to build Svelte apps.
</p>
<p>
	This template is pre-configured with svlete-spa-router for routing.<br />
	Visit the
	<a href="https://github.com/ItalyPaleAle/svelte-spa-router"
		>documentation for the router</a
	> to learn more.
</p>
<p>
	Check a route: <a href="#/lorem/2">Lorem ipsum</a>
</p>

{#await fetchRooms()}
	<p>Waiting to retrieve rooms...</p>
{:then rooms_json}
	<ul style="list-style: none">
		{#each rooms_json["data"] as room}
		<li>
			<a href={`#/room/${room.id}`}>{room.name}</a>
		</li>
		{/each}
	</ul>
{:catch error}
	<p style="color: red">{error.message}</p>
{/await}

<style>
	h1 {
		color: #ff3e00;
		text-transform: uppercase;
		font-size: 4em;
		font-weight: 100;
	}
</style>
