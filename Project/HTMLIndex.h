EMBED_FILE(

<!doctype html>
<html>
  <head>
    <title>How To Basil</title>
    <link rel="stylesheet" href="stylesheet.css">
    <script>
      function sendCommand(command)
      {
        fetch(command, 
        {
          method: 'POST',
          headers: {},
          body: {},
        });
      }
    </script>
  </head>
  <body>
    <header>
      <h1>How To Basil</h1>
      <nav>
        <a href="#Panel">Panel</a>
        <a href="#Settings">Settings</a>
        <a href="https://github.com/HITOA/HowToBasil">Github</a>
      </nav>
    </header>
    <main id="content"></main>
    <script>
      const pairUriHash = {
        "#Panel": "/panel.html",
        "#Settings": "/settings.html"
      };
      async function loadContent() {
        let contentContainer = document.getElementById("content");
        console.log(contentContainer);
        let uri = pairUriHash[location.hash];
        let content = await fetch(uri);
        if (!content.ok) {
          contentContainer.innerHTML = content.status;
          return;
        }
        contentContainer.innerHTML = await content.text();
      }

      if (!location.hash)
        location.hash = "#Panel";

      loadContent();
      window.addEventListener("hashchange", loadContent);
    </script>
  </body>
</html>

)