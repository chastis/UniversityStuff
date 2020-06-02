<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<html>
    <head>
        <title>Hello Page</title>
    </head>
    <body>
        <h2>Hello, ${login}!</h2>
        <form method="post" action="client">
            <input type="text" id="login" name="info" />
            <input type="text" id="money" name="money" />
            <select name="card">
                <c:forEach items="${cards}" var="card">
                    <option value="${card.cardNumber}">${card.cardNumber}</option>
                </c:forEach>
            </select>

            <select>
                <c:forEach items="${names}" var="name">
                <option value="${name}">${name}</option>
                </c:forEach>
            </select>
        </form>
    </body>
</html>

