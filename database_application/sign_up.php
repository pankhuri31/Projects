<html>
<?php
require("res/config.php");
?>
<head>
<title>Irrigation Enterprise</title>
<LINK REL=StyleSheet HREF="style.css" TYPE="text/css" >
<style>
.table
{
margin-top:10px;
margin-left:400px;
}
#al
{
margin-left:700px;
}
#h
{
color:white;
font-family:"Comic Sans MS", cursive, sans-serif;
}
</style>
</head>
<body>
	<div id="header">
	<h1 id="h">Register</h1>
	</div>

<form action="" method="POST">
<table class="table">
<tr>
<td>User Name</td>
<td><input type="text" name="login"/>
</tr>
<tr>
<td>Password</td>
<td><input type="password" name="pwd"/>
</tr>
<tr>
<td>Confirm Password</td>
<td><input type="password" name="pwd1"/>
</tr>
</table>
<br/><br/>
<input type="submit" value="submit" name="submit" id="al"/>
</form>

<?php

if(!empty($_POST['login']) && !empty($_POST['pwd']) && !empty($_POST['pwd1']) && isset($_POST['login'],$_POST['pwd'],$_POST['pwd1'],$_POST['submit']))
{
if($_POST['pwd']==$_POST['pwd1'])
{
mysql_query("INSERT INTO members (username,passwd) 
VALUES('$_POST[login]','$_POST[pwd]')");

$sql1 =	mysql_query("CREATE USER '$_POST[login]'@'localhost'  IDENTIFIED BY  '$_POST[pwd]' ");
$sql2 = mysql_query("GRANT SELECT ON  `irrigation enterprise` . * TO  '$_POST[login]'@'localhost' ");
if($sql1 and $sql2)echo ":)";
else echo ":(";
//$sql = mysql_query("select User from mysql.user");
//echo mysql_num_rows($sql); 
//while($row = mysql_query("show columns from mysql.user")){
	//	echo $row['User'];
		//}

session_start();
$_SESSION['user']=trim($_POST['login']);
$_POST['login']=' ';
$_POST['pwd']=' ';
//header("Location:index.php");
}
else 
{
echo "<h3> Passwords dont match</h3>";
}
}
else if(isset($_POST['submit']))
{
echo "<h1>Fill in all the fields</h1>";
}
?>
</body>
</html>