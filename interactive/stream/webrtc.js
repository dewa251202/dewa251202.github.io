const startWhepBtn = document.getElementById("play-btn");
startWhepBtn.addEventListener("click", () => {
    const appName = document.getElementById("app-name")?.value ?? '';
    const streamName = document.getElementById("stream-name")?.value ?? '';
    const token = document.getElementById("token").value;
    const useHeader = document.getElementById("use-header")?.checked ?? false;
    //Create peerconnection
    const pc = window.pc = new RTCPeerConnection();
    //Add recv only transceivers
    pc.addTransceiver("audio");
    pc.addTransceiver("video");
    pc.ontrack = (event) => {
        console.log(event)
        if (event.track.kind == "video") {
            var player = document.getElementById('local-video')
            player.srcObject = event.streams[0]
            player.controls = true
        }
    }
    //Create whep client
    const whep = new WHEPClient();
    // const host = location.origin;
    const host = 'https://known-violently-whippet.ngrok-free.app';
    const url = host + "/whep?app=" + appName + "&stream=" + streamName + (!useHeader ? "&token=" + token : "");
    //const token = ""
    //Start viewing
    whep.view(pc, url, useHeader ? token : null);
});