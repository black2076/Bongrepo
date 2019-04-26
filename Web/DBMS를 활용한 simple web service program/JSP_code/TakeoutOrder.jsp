<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<%@ page import ="java.sql.*" %>
    
<!DOCTYPE html>
<html>
<head>
<meta charset="EUC-KR">
<title>감사합니다</title>
</head>
<body>
	<h3>감사합니다</h3>
	<% 
		String cusname = request.getParameter("cusname");
	
	 Connection conn=null;
	 PreparedStatement pstmt = null;
	
	 String driver = "oracle.jdbc.driver.OracleDriver";
	 String url = "jdbc:oracle:thin:@localhost:1521:orcl";
	 
   	try{
   	    Class.forName(driver);
   	    conn=DriverManager.getConnection(url,"system","1234qwer");
   	   
   	    String query="DELETE FROM ORDERSHEET where CUSTOMERNAME=?";
   	    pstmt = conn.prepareStatement(query);
   	    pstmt.setString(1,cusname);
   	    pstmt.executeUpdate();
   	    
   	    pstmt.close();
   	    conn.close();
   	  
   	}catch(Exception e){
   	    e.printStackTrace();
   	}
		
   		response.sendRedirect("OrderConfirm.jsp");
	%>
</body>
</html>