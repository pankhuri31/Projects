<?php
session_start();
require("res/config.php");
?>
<html>
<head>
<link rel="stylesheet" type="text/css" href="style.css" />
<style>
</style>
</head>
<body>
<?php
if (!isset($_SESSION['user']))
{
echo "<h1>you are not logged in</h1>";
}
else
{
echo "<h1>You have successfully logged out :)</h1>";
}
?>
</body>
<?php
unset($_SESSION['valid'],$_SESSION['user']);
session_destroy();
?>
</html>