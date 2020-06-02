<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@taglib uri="http://www.springframework.org/tags" prefix="spring"%>
<head>
        <title>Admin</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js" integrity="sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>


</head>
<html>
	<body>
		<h1>Admin panel</h1>
		<h2>Hello, <c:out value="${sessionScope.loggedinuser}" />!</h2><a  href="<c:url value='/logout'/>">Logout</a>

		<h4>${sessionScope.bankName} bank</h4>
		<form method="post" action='<spring:url value="/operation"/>' id="unblockForm"
              style="width:30%; margin:20px; padding:10px; border: 2px solid LightGray;border-radius:5px;">
			<c:forEach items="${blockedCards}" var="item">
				Card Number: ${item.cardNumber}
				<input type="submit"  name="submit" value="Unblock" onclick="unblock(${item.cardNumber})"
                       class="btn btn-danger">
				<br>
			</c:forEach>
			<input type="hidden" name="card" id="cardNum"/>
			<input type="hidden" name="command" id="command"/>

		</form>
		<script>
			function unblock(cardNumber)
			{
				document.getElementById("cardNum").value = cardNumber;
				document.getElementById("command").value = "Unblock";
				var form = document.getElementById("unblockForm");
				form.submit();
			}
		</script>
	</body>
</html>