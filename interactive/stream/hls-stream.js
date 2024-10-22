const video = document.getElementById('local-video');
const token = document.getElementById('token');

function playVideo(){
    if (Hls.isSupported()) {
        const hls = new Hls({
            xhrSetup: (xhr, url) => {
                xhr.setRequestHeader("ngrok-skip-browser-warning", true);
                xhr.setRequestHeader("authorization", "Bearer " + token.value);
            }
        });
        hls.on(Hls.Events.MEDIA_ATTACHED, function () {
            console.log('video and hls.js are now bound together!');
        });
        hls.on(Hls.Events.MANIFEST_PARSED, function (_event, data) {
            video.play();
            console.log('manifest loaded, found ' + data.levels.length + ' quality level');
        });

        // const address = 'http://localhost:8080';
        const address = 'https://known-violently-whippet.ngrok-free.app';
        const source = `${address}/Streams/live/live.m3u8`
        hls.loadSource(source);
        // bind them together
        hls.attachMedia(video);
    }
}

const playButton = document.getElementById("play-btn");
playButton?.addEventListener("click", playVideo);
// video.addEventListener("play", playVideo);