<head>
    <meta charset="utf-8">
    <link rel="stylesheet" href="css/loginStyle.css">
</head>
<body>
<form method="post" action="login">
    <div>
        <p>
            <label for="login-input">Login:</label>
            <input type="text" name="login" id="login-input" value="Login" pattern="[a-zA-Z0-9]{1,30}">
        </p>

        <p>
            <label for="pass-input">Password:</label>
            <input type="password" name="pass" id="pass-input" value="4815162342" pattern="[a-zA-Z0-9]{1,30}">
        </p>

        <p class="login-submit">
            <button type="submit" class="login-button" id="say-hello-button">Sign In</button>
        </p>
    </div>
</form>
</body>
</html>
