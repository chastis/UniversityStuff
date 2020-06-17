<!DOCTYPE html>
<html lang="html">
<link rel="stylesheet" href="style.css">
<body>

<div id="info">
    <div class="container-name">
        <div class="div1">StartPoint</div>
        <div class="div2"><select id="point1"> </select></div>
        <div class="div1">EndPoint</div>
        <div class="div2"><select id="point2"></select></div>

        <div>
            <button type="button" iD="btn" onclick="start()">Start!</button>
        </div>
    </div>
</div>

<div id="image"></div>

<script src="three.js"></script>
<script src="controls/OrbitControls.js"></script>
<script src="controls/TransformControls.js"></script>
<script src="script.js"></script>
</body>
</html>
