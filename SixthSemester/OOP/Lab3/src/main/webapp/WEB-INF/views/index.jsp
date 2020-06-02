<html>
    <head>
        <title>Spring 4 Security Example</title>
    </head>
    <body>
      <h3>You are not authorized to access user profile.</h3>
      <form action="<%=request.getContextPath()%>/appLogout" method="POST">
        <input type="submit" value="Logout"/>
      </form> 
    </body>
</html> 