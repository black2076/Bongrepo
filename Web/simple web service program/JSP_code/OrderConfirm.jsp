<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
    <%@ page import = "java.sql.*" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="EUC-KR">
<title>���� ���� �ֹ� Ȯ��</title>
</head>
<body>
	<h3>�ֹ��� �޾��ּ���</h3>
	<%
  		 Connection conn=null;
    	 Statement stmt = null;
    	 
    	 PreparedStatement pstmt = null;
    	 
    	 ResultSet rs = null;
		 String driver = "oracle.jdbc.driver.OracleDriver";
		 String url = "jdbc:oracle:thin:@localhost:1521:orcl";
 		 
	    	try{
	    	    Class.forName(driver);
	    	    conn=DriverManager.getConnection(url,"system","1234qwer"); //�ڽ��� ���̵�� ��й�ȣ
	    	   
	    	
	    	    String query="SELECT * FROM ORDERSHEET";
	    	   stmt = conn.createStatement();
	    
	    	   rs = stmt.executeQuery(query);
	    
    %>
    
    <table border="1" >
    <tr>
    	<td>���̸�</td>
    	<td>�ܹ���</td>
    	<td>���̵�޴�</td>
    	<td>����</td>
    	<td>����</td>
    	
    	<td>�ֹ� �ޱ�</td>
    </tr>
    
    
    <%
    	while(rs.next()){
    %>
    <tr>
    <td><%=rs.getString("CUSTOMERNAME") %></td>
    <td><%=rs.getString(2) %></td>
    <td><%=rs.getString(3) %></td>
    <td><%=rs.getString(4) %></td>
    <td><%=rs.getString(5) %></td>
    
    <td>
    <A href="TakeoutOrder.jsp?cusname=<%=rs.getString("CUSTOMERNAME") %>">�ޱ�</A>
    </td>
    </tr>
    <%
    	}
    %></table>
    
    <%
    	rs.close();
    	stmt.close();
    	conn.close();
    	
	    }catch(Exception e){
	    	    e.printStackTrace();
	    }
    %>
    
    
    
</body>
</html>