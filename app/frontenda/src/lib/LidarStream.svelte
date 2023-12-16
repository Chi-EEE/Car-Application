<script lang="ts">
    import { onMount } from "svelte";
    import { get } from "svelte/store";

    import { websocket_store } from "./WebsocketStore";

    class ScanPoint {
        constructor(angle: number, distance: number) {
            this.angle = angle;
            this.distance = distance;
        }

        readonly angle: number;
        readonly distance: number;
    }

    let points: Array<ScanPoint> = [];

    const websocket = get(websocket_store);

    websocket!!.addEventListener("message", (event: MessageEvent<any>) => {
        const json_data = JSON.parse(event.data);
        if (json_data.type == "car") {
            points.length = 0;
            console.log(json_data["data"].length);
            for (const point of json_data["data"]) {
                points.push(new ScanPoint(point.angle, point.distance));
            }
            draw();
        }
    });

    let canvas: HTMLCanvasElement;
    let context: CanvasRenderingContext2D;

    function clear() {
        context.clearRect(0, 0, canvas.width, canvas.height);
        context.fillStyle = "black";
        context.fillRect(0, 0, canvas.width, canvas.height);
    }

    function draw() {
        console.log("Drawing");
        clear();
        context.fillStyle = "green";
        
        for (const point of points) {
            const angle = point.angle;
            const distance = point.distance * 0.3;
            const angleInRadians = angle * (3.14159265 / 180.0);
            const x = distance * Math.cos(angleInRadians);
            const y = distance * Math.sin(angleInRadians);
            context.fillRect(x + (canvas.width / 2), y + (canvas.height / 2), 10, 10);
        }
    }

    onMount(async () => {
        context = canvas.getContext("2d")!!;
        clear();
    });
</script>

<canvas id="canvas" width="800" height="600" bind:this={canvas}></canvas>