import { readable, writable, derived, type Readable, type Writable } from "svelte/store";

export let websocket_url_store: Writable<string | undefined> = writable();

export const websocket_store: Readable<WebSocket | undefined> = derived([websocket_url_store], ([$websocket_url]) => {
    if ($websocket_url === undefined) {
        return undefined;
    }
    return new WebSocket($websocket_url);
});