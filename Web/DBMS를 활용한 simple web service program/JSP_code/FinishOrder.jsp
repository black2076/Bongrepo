<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
 
 <%@ page import="java.sql.*" %>  
    
    <%
    	String cusname = (String) session.getAttribute("CUSNAME");
    	String hamburg = (String) session.getAttribute("HAMBURG");
   	 	String sidemenu = (String) session.getAttribute("SIDEMENU");
   	 	String drink = (String) session.getAttribute("DRINK");
  	 	int totalprice = (Integer) session.getAttribute("TOTALPRICE");
    %>
    
    <%
  		 Connection conn=null;
    	 PreparedStatement pstmt = null;
		 String driver = "oracle.jdbc.driver.OracleDriver";
		 String url = "jdbc:oracle:thin:@localhost:1521:orcl";
 		
	    	try{
	    	    Class.forName(driver);
	    	    conn=DriverManager.getConnection(url,"system","1234qwer"); //자신의 아이디와 비밀번호
	    	   
	    	    String sql = "insert into ORDERSHEET values(?,?,?,?,?)";
	    	    pstmt = conn.prepareStatement(sql);
	    	    pstmt.setString(1,cusname);
	    	    pstmt.setString(2,hamburg);
	    	    pstmt.setString(3,sidemenu);
	    	    pstmt.setString(4,drink);
	    	    pstmt.setInt(5,totalprice);
	    	    pstmt.executeUpdate();
	    	}catch(Exception e){
	    	    e.printStackTrace();
	    	}
	    	
	    	session.invalidate();
    %>
<!DOCTYPE html>
<html>
<head>
<meta charset="EUC-KR">
<title>주문 완료</title>
</head>
<body>
	<h2>주문이 완료되었습니다.</h2> <br><br>
	<font size = 4>잠시만 기다려주세요</font>
</body>
</html>