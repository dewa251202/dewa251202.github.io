document.querySelectorAll('.spoiler').forEach(spoiler => {
    const marker = spoiler.querySelector('span');
    const title = spoiler.querySelector('.spoiler-title');
    const content = spoiler.querySelector('.spoiler-content');

    title.addEventListener('click', () => {
        content.classList.toggle('hidden');
        marker.innerText = marker.innerText === '+ ' ? '- ' : '+ ';
    });
});