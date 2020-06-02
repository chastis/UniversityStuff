<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib uri = "http://java.sun.com/jsp/jstl/functions" prefix = "fn" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<html>
    <head>
        <title>Hello Page</title>
    </head>
    <body>
        <p style="color: red">  <c:out value = "${warning}"/></p>
        <p style="color: green">  <c:out value = "${topup}"/></p>
        <h2>Hello, ${fn:escapeXml(sessionScope.User.name)}!</h2>
        <!-- ------------------------------------------------------------------------ -->
        <c:forEach items="${cardAccountMap}" var="item">
            Card Number: ${item.key.cardNumber} ----- ${item.value.moneyAmount}$<br>
        </c:forEach>
        <!-- ------------------------------------------------------------------------ -->
        <form method="post" action="client" id="payForm">
            Info:
            <input type="text" id="info" name="info" />
            Money:
            <input type="text" id="money" name="money" />
            Card:
            <select name="card">
                <c:forEach items="${cardAccountMap}" var="card">
                    <option value="${card.key.cardNumber}">${card.key.cardNumber}</option>
                </c:forEach>
            </select>
            <input type="hidden" name="command" id="commandPay"/>
            <input type="submit" id="submitPay" name="submit" value="Add payment" onclick="setCommand('Pay', 'payForm')">
        </form>
        <br>
        <br>
        <br>
        <!-- ------------------------------------------------------------------------ -->
        <form method="post" action="client" id="topUpForm">
            Money:
            <input type="text" id="topUpMoney" name="money" />
            Card:
            <select name="card">
                <c:forEach items="${cardAccountMap}" var="card">
                    <option value="${card.key.cardNumber}">${card.key.cardNumber}</option>
                </c:forEach>
            </select>
            <input type="hidden" name="command" id="commandTopUp"/>
            <input type="submit" id="submitTopUp" name="submit" value="Top up account" onclick="setCommand('TopUp', 'topUpForm')" >
        </form>

        <!-- ------------------------------------------------------------------------ -->
        <form method="post" action="client" id="blockForm">
            Card:
            <select name="card">
                <c:forEach items="${cardAccountMap}" var="card">
                    <option value="${card.key.cardNumber}">${card.key.cardNumber}</option>
                </c:forEach>
            </select>
            <input type="hidden" name="command" id="commandBlock"/>
            <input type="submit" id="submitBlock" name="submit" value="Block" onclick="setCommand('Block', 'blockForm')" >
        </form>
        <!-- ------------------------------------------------------------------------ -->
        <script>
            function setCommand(command, formName)
            {
                document.getElementById("command" + command).value = command;
                var form = document.getElementById(formName);
                form.submit();
            }
        </script>
        <br>
        <br>
        <br>

        <table>
            <c:forEach items="${sessionScope.Payments}" var="item">
                <tr>
                    <td><c:out value="${item}" /></td>
                </tr>
            </c:forEach>
        </table>
    </body>
</html>

