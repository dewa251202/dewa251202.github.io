document.querySelectorAll('.spoiler').forEach(spoiler => {
    const marker = spoiler.querySelector('span');
    const title = spoiler.querySelector('.spoiler-title');
    const content = spoiler.querySelector('.spoiler-content');

    title.addEventListener('click', () => {
        content.classList.toggle('hidden');
        marker.innerText = marker.innerText === '+ ' ? '- ' : '+ ';
    });
});

function getLocaleDateString(date){
    const year = date.getFullYear().toString().padStart(4, '0');
    const month = String(date.getMonth() + 1).padStart(2, '0');
    const day = date.getDate().toString().padStart(2, '0');
    return `${year}-${month}-${day}`;
}