const { ipcRenderer, contextBridge } = require('electron')

const WINDOW_API = {
    getLocalIPList: () => ipcRenderer.invoke("getLocalIPList"),

    startWebSocketServer: (/** @type {number} */ port) => ipcRenderer.invoke("startWebSocketServer", port),
    closeWebSocketServer: () => ipcRenderer.invoke("closeWebSocketServer"),
    getWebSocketServer: () => ipcRenderer.invoke("getWebSocketServer"),

    isConnected: () => ipcRenderer.invoke("isConnected"),

    onMessage: (/** @type {(string) => void} */ callback) => ipcRenderer.on('onMessage', (_event, /** @type {string} */ value) => callback(value)),
    
    onConnection: (/** @type {(any) => void} */ callback) => ipcRenderer.on('onConnection', (_event, /** @type {any} */ args) => callback(args)),
    onDisconnection: (/** @type {(any) => void} */ callback) => ipcRenderer.on('onDisconnection', (_event, /** @type {any} */ args) => callback(args)),

    selectRaspberryPi: (/** @type {string} */ uuid) => ipcRenderer.invoke("selectRaspberryPi", uuid),
    unselectRaspberryPi: () => ipcRenderer.invoke("unselectRaspberryPi"),
    getRaspberryPiList: () => ipcRenderer.invoke("getRaspberryPiList"),
    getSelectedRaspberryPi: () => ipcRenderer.invoke("getSelectedRaspberryPi"),
}

contextBridge.exposeInMainWorld("api", WINDOW_API)