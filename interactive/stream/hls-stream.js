const video = document.getElementById('local-video');

function playVideo(){
    if (Hls.isSupported()) {
        const hls = new Hls({
            xhrSetup: xhr => {
                xhr.setRequestHeader("ngrok-skip-browser-warning", true)
            }
        });
        hls.on(Hls.Events.MEDIA_ATTACHED, function () {
            console.log('video and hls.js are now bound together!');
        });
        hls.on(Hls.Events.MANIFEST_PARSED, function (_event, data) {
            console.log('manifest loaded, found ' + data.levels.length + ' quality level');
        });

        // const address = 'http://localhost:8080';
        const address = 'https://known-violently-whippet.ngrok-free.app';
        const source = `${address}/Streams/live/live.m3u8`
        hls.loadSource(source);
        // bind them together
        hls.attachMedia(video);
        video.play();
    }
}

const playButton = document.getElementById("play-btn");
playButton?.addEventListener("click", playVideo);
// video.addEventListener("play", playVideo);