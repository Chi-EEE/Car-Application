import Home from './routes/Home.svelte';
import Lorem from './routes/Lorem.svelte';
import Room from './routes/Room.svelte';
import NotFound from './routes/NotFound.svelte';

export default {
    '/': Home,
    '/lorem/:repeat': Lorem,
    '/room/:room_name': Room,
    // The catch-all route must always be last
    '*': NotFound
};
