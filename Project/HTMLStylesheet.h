EMBED_FILE(

:root {
    --color-a: #292929;
    --color-b: #404040;
    --color-c: #f0f0f0;
    --color-d: #5bc2a3;
}

html {
    font-family: Arial, Helvetica, sans-serif;
}

body {
    background-color: var(--color-a);
    margin: 0%;
}

header {
    display: flex;
    align-items: center;
    text-align: center;
    background-color: var(--color-b);
    padding: 10px;
}

header h1 {
    font-size: 3rem;
    color: var(--color-d);
}

nav {
    margin-left: 10%;
}

nav a {
    background-color: var(--color-d);
    color: var(--color-c);
    text-decoration: none;
    font-weight: bold;
    padding: 15px 25px;
    display: inline-block;
    border-radius: 10px;
}

main {
    color: var(--color-c);
}

.horizontal-box {
    display: flex;
}

.panel-container {
    display: flex;
}

.panel {
    margin: 3%;
}

.panel-header {
    background-color: var(--color-d);
    border-radius: 10px;
    padding: 2%;
}

.panel-header h1 {
    font-size: 2rem;
    margin: 0%;
}

.panel-header h2 {
    font-size: 1rem;
    margin: 0%;
    margin-right: 20px;
}

.panel table {
    background-color: var(--color-b);
}

)