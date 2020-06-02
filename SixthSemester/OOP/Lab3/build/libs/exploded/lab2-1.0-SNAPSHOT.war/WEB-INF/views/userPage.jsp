
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@taglib uri="http://www.springframework.org/tags" prefix="spring"%>
<html>
    <head>
        <title>Title</title>
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
        <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js" integrity="sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1" crossorigin="anonymous"></script>
        <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>


    </head>
    <c:if test="${success != null}">
        <h1>${success}</h1>
    </c:if>
    <c:if test="${warning != null}">
        <div class="alert alert-danger">
            <p style="color: red">  <c:out value = "${warning}"/></p>
        </div>
    </c:if>
    <c:if test="${topup != null}">
        <div class="alert alert-success">
            <p style="color: green">  <c:out value = "${topup}"/></p>
        </div>
    </c:if>
    <h2>Hello, <c:out value="${sessionScope.loggedinuser}" />!</h2><a  href="<c:url value='/logout'/>">Logout</a><br/>
    <!-- ------------------------------------------------------------------------ -->
    <c:forEach items="${sessionScope.cardAccountMap}" var="item">
        Card Number: ${item.key.cardNumber} ----- ${item.value.moneyAmount}$<br>
    </c:forEach>
    <!-- ------------------------------------------------------------------------ -->
    <div class="container">
        <div class="row">
            <div class="col-sm">
                <form method="post" action='<spring:url value="/operation"/>' id="payForm"
                      style=" margin:20px;  padding:10px; border: 2px solid LightGray;border-radius:5px;">
                    Info:
                    <div class="form-row align-items-center">
                        <input type="text" id="info" name="info" class="form-control" />
                    </div>
                    Money:
                    <div class="form-row align-items-center">
                        <input type="text" id="money" name="money" class="form-control" />
                    </div>
                    Card:
                    <div class="form-row align-items-center">
                        <select name="card">
                            <c:forEach items="${sessionScope.cardAccountMap}" var="card">
                                <option value="${card.key.cardNumber}">${card.key.cardNumber}</option>
                            </c:forEach>
                        </select>
                    </div>
                    <br/>
                    <input type="hidden" name="command" id="commandPay"/>
                    <input type="submit" id="submitPay" name="submit" value="Add payment" onclick="setCommand('Pay', 'payForm')"
                           class="btn btn-primary">
                </form>
            </div>
            <!-- ------------------------------------------------------------------------ -->
            <div class="col-sm">
                <form method="post" action='<spring:url value="/operation"/>' id="topUpForm"
                      style=" margin:20px;  padding:10px; border: 2px solid LightGray;border-radius:5px;">
                    Money:
                    <div class="form-row align-items-center">
                        <input type="text" id="topUpMoney" name="money" class="form-control" />
                    </div>
                    Card:
                    <div class="form-row align-items-center">
                        <select name="card">
                            <c:forEach items="${sessionScope.cardAccountMap}" var="card">
                                <option value="${card.key.cardNumber}">${card.key.cardNumber}</option>
                            </c:forEach>
                        </select>
                    </div>
                    <br/>
                    <input type="hidden" name="command" id="commandTopUp"/>
                    <input type="submit" id="submitTopUp" name="submit" value="Top up account" onclick="setCommand('TopUp', 'topUpForm')"
                           class="btn btn-success">
                </form>
            </div>
            <!-- ------------------------------------------------------------------------ -->
            <div class="col-sm">
                <form method="post" action='<spring:url value="/operation"/>' id="blockForm"
                      style=" margin:20px;  padding:10px; border: 2px solid LightGray;border-radius:5px;">
                    Card:
                    <div class="form-row align-items-center">
                        <select name="card">
                            <c:forEach items="${sessionScope.cardAccountMap}" var="card">
                                <option value="${card.key.cardNumber}">${card.key.cardNumber}</option>
                            </c:forEach>
                        </select>
                    </div>
                    <br/>
                    <input type="hidden" name="command" id="commandBlock"/>
                    <input type="submit" id="submitBlock" name="submit" value="Block" onclick="setCommand('Block', 'blockForm')"
                           class="btn btn-danger">
                </form>
            </div>
        </div>
    </div>
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
    <form method="post" action='<spring:url value="/operation"/>' id="dateForm"
          style="width:30%; margin:20px; padding:10px; border: 2px solid LightGray; border-radius:5px;">
        Card:
        <div class="form-row align-items-center">
            <select name="card">
                <c:forEach items="${sessionScope.cardAccountMap}" var="card">
                    <option value="${card.key.cardNumber}">${card.key.cardNumber}</option>
                </c:forEach>
            </select>
        </div>
        Date from:
        <div class="form-row align-items-center">
            <input type="date" name="dateFrom"  class="form-control">
        </div>
        Date to:
        <div class="form-row align-items-center">
            <input type="date" name="dateTo"  class="form-control">
        </div>
        <input type="hidden" name="command" id="commandDate"/>
        <input type="submit" id="submitDate" name="submit" value="Calculate" onclick="setCommand('Date', 'dateForm')"
               class="btn btn-info">
    </form>
    <c:if test="${leftDate != null}">

        <div id=container >
            <canvas id='canvas' width='500' height='500' style="border: 1px solid black;"></canvas>
        </div>
        <script type="text/javascript" >
            function draw(operations, blocksize, ld, rd) {
                array = (operations).split(',');
                var blockInOne = 250 / blocksize;
                leftDate =ld
                rightDate = rd
                rects = []
                var prevEnd = 250
                for(var i = 0; i < array.length; i++){
                    var height =  Math.abs(parseInt(array[i])) * blockInOne;
                    if(parseInt(array[i]) < 0){
                        rects.push({x:(i + 1)*10 + 2, y: prevEnd, w: 7, h: height});
                    }
                    else{
                        rects.push({x:(i + 1)*10 + 2, y: prevEnd - height, w: 7, h: height});
                    }
                    prevEnd -= parseInt(array[i]) * blockInOne;

                }
                rects.push({x:0, y:0, w:0, h:0});
                array.push("0");
                var canvas = document.getElementById('canvas');
                var context = canvas.getContext('2d');
                drawColumns(canvas);
                i = 0
                while(r = rects[i]){



                    context.beginPath();
                    context.rect(r.x, r.y, r.w, r.h);
                    if(parseInt(array[i]) > 0){
                        context.fillStyle = "green";
                    }
                    else{
                        context.fillStyle = "red";
                    }
                    context.fill();
                    i++;

                }



                canvas.onmousemove = function(e) {
                    var rect = this.getBoundingClientRect(),
                        x = e.clientX - rect.left,
                        y = e.clientY - rect.top,
                        i = 0, r;

                    context.clearRect(0, 0, canvas.width, canvas.height);
                    drawColumns(canvas);
                    tooltip  = [];


                    while(r = rects[i]){
                        context.beginPath();
                        context.rect(r.x, r.y, r.w, r.h);
                        if(context.isPointInPath(x, y)){
                            context.fillStyle = "blue";
                            context.fill();
                            tooltip.push({text:array[i] + '$', x: x - 20, y: y - 10});
                        }
                        else{
                            if(parseInt(array[i]) > 0){
                                context.fillStyle = "green";
                            }
                            else{
                                context.fillStyle = "red";
                            }

                        }

                        context.fill();
                        i++;
                    }
                    i = 0

                    while(t = tooltip[i]){
                        context.beginPath();
                        context.fillStyle = "black";
                        context.font = "40px Georgia";
                        context.fill();
                        context.fillText(t.text, t.x, t.y);
                        i++;
                    }
                    context.font = "20px Georgia";

                }



            }

            function drawColumns(canvas) {
                if (canvas.getContext) {
                    var context = canvas.getContext('2d');

                    for(var x=0.5;x<500;x+=10) {
                        context.moveTo(x,0);
                        context.lineTo(x,500);
                    }

                    for(var y=0.5; y<500; y+=10) {
                        context.moveTo(0,y);
                        context.lineTo(500,y);

                    }
                    context.moveTo(0,249);
                    context.lineTo(500,249);
                    context.moveTo(0,250);
                    context.lineTo(500,250);
                    context.moveTo(0,251);
                    context.lineTo(500,251);
                    context.strokeStyle='gray';
                    context.stroke();

                    context.fillStyle = "black";
                    context.font = "11px Georgia";
                    context.fillText(leftDate, 0, 495);
                    context.fillText(rightDate, rects.length * 10 - 10, 495);




                }
            }
            draw("${candles}", ${maxValue}, "${leftDate}", "${rightDate}");
        </script>
    </c:if>
    <ul class="list-group">
        <c:forEach items="${sessionScope.payments}" var="item">
            <li class="list-group-item">
                <c:out value="${item}" />
            </li>
        </c:forEach>
    </ul>
    </body>
</html>
