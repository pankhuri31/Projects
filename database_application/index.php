<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">

<html>

<head>
<title>Irrigation Enterprise</title>
<LINK REL=StyleSheet HREF="style.css" TYPE="text/css" MEDIA=screen>
<style>
#menulinks {
clear:both;
width:875px;
height:50px;
padding-left:25px;
background-image:url(images/menulinks.png);
}

#menulinks a {
display:block;
background-image:none;
padding-top:14px;
height:31px;
color:#FFFFFF;
font-weight:bold;
font-size:14px;
text-transform:uppercase;
float:left;
padding-left:15px;
padding-right:15px;
margin-left:5px;
margin-right:5px;
}

#menulinks a:hover, #menulinks a:hover.active {
background-image:url(images/menuhover.png);
text-decoration:none;
}

.menuline {
width:2px;
display:block;
background-image:url(images/menuline.png);
height:35px;
float:left;

}

#mainarea {
width:860px;
clear:both;
padding-left:40px;
}

#contentarea {
width:568px;
padding-right:10px;
float:left;
line-height:40pt;
font-size:15pt;
}

#sidebar {
float:left;
width:265px;
background-image:url(images/sidebartop.png);
background-repeat:no-repeat;
line-height:14pt;
}

#sidebar a {
width:255px;
padding-left:10px;
background-image:none;
clear:both;
padding-top:6px;
height:24px;
display:block;
}

#sidebar a:hover {
background-image:url(images/sidebarlinkhover.png);
text-decoration:none;
background-repeat:no-repeat;
}

#footer {
width:900px;
clear:both;
height:35px;
padding-top:30px;
text-align:center;
line-height:14pt;
background-image:url(images/footer.png);
background-repeat:no-repeat;
background-color:#000000;
}
</style>
</head>

<body>
<?php

session_start();
require("res/config.php");
//echo $_SESSION['user'];
?>
<div id="page">
	<div id="header">
			<h1><a href="#">Irrigation Enterprise</a></h1>

	</div>
	
	<div id="menulinks">
		<a class="active" href="login.php"><span>Login</span></a>	
		<div class="menuline"></div>
		<a href="sign_up.php"><span>Register</span></a>
		<div class="menuline"></div>
		<a href="logout.php"><span>Log out</span></a>
		<div class="menuline"></div>
		<a href="#"><span>Contact Us</span></a>
		<div class="menuline"></div>
	</div>
	
	
	<div id="mainarea">
	<div id="contentarea">
		
		<a href='view.php'>View Relations</a>
		</br>
		
		<?php
		if(isset($_SESSION['user'])){
		$sql=mysql_query("select type from members where username='$_SESSION[user]'");
		$row=mysql_fetch_array($sql);
		if($row['type']==1)
		{
			echo "<a href='admin.php'>Administrative Interface</a>
		</br><a href='insert_table.php'>Insert</a>
		</br>
		<a href='delete_tuple.php'>Delete</a>
		</br><a href='update_tuple.php'>Update</a>
		</br>";
		}
		}
		?>

	</div>
	
	<div id="sidebar">
	</div></div>
	
	<div id="footer">		
	</div>


</div>

</body>

</html>