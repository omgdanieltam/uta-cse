package sample;

import static org.junit.jupiter.api.Assertions.*;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;

import org.junit.jupiter.api.Test;

/**
* @author Jack Feng
*/

class SampleProgramTest {
	
    /**
     * Tests for capitalize_first_ch()
     * input:      boolean flag, String name
     * output:     String
     * ------------------------------
     * Test cases:
     * true, "john"		======>	"John"
     * false, "John"	======> "John"
     * ------------------------------
     */
	@Test
	void testCapitalize_first_ch() {
		System.out.println("testing capitalize_first_ch().");
		
		SampleProgram instance = new SampleProgram();
		assertEquals("John", instance.capitalize_first_ch(true, "john"));
		assertEquals("John", instance.capitalize_first_ch(false, "John"));
		
		System.out.println("capitalize_first_ch() finished.");
	}
	
    /**
     * Tests for add_user()
     * input:      String name, int permission_level, int type
     * output:     String[]
     * ------------------------------
     * Test cases:
     * "john", 0, 0	======>	"John"
     * "John", 0, 1	======>	"John"
     * ------------------------------
     */
	@Test
	void testAdd_user() {
		System.out.println("testing add_user().");
		
		SampleProgram instance = new SampleProgram();
		assertArrayEquals(new String[] {"John", "faculty"}, instance.add_user("john", 0, 0));
		assertArrayEquals(new String[] {"John", "student"}, instance.add_user("John", 0, 1));
		
		System.out.println("add_user() finished.");
	}
	
    /**
     * Tests for main()
     * input:      String[] args
     * output:     Console Output
     * ------------------------------
     * Test cases:
     * [], Console Input = "john 3 0"	======>	"Adding user \"John\".\nfaculty user John added.\n"
     * ["John", "0", "5"]				======>	"Adding user \"John\".\nadding user failed. \n"
     * ------------------------------
     */
	@Test
	void testMain() throws IOException {
		System.out.println("testing main().");
		PrintStream stdout = System.out;
		InputStream stdin = System.in;
		
		ByteArrayOutputStream actual_output = new ByteArrayOutputStream();
		System.setOut(new PrintStream(actual_output));
		ByteArrayInputStream input = new ByteArrayInputStream("John 0 0".getBytes());
		System.setIn(input);
		SampleProgram.main(new String[] {});
		assertEquals("Adding user \"John\".\nfaculty user John added.\n", actual_output.toString());
		
		actual_output = new ByteArrayOutputStream();
		System.setOut(new PrintStream(actual_output));
		SampleProgram.main(new String[] {"John", "0", "5"});
		assertEquals("Adding user \"John\".\nadding user failed. \r\n", actual_output.toString());
		
		System.setOut(stdout);
		System.setIn(stdin);
		System.out.println("main() finished.");
	}
	
    /**
     * End-to-End Test cases:
     * [], Console Input = "john 3 0"	======>	"Adding user \"john\".\nfaculty user John added.\n"
     * ["John", "0", "5"]				======>	"Adding user \"John\".\nadding user failed. \n"
     * ------------------------------
     */
	@Test
	void testEndToEnd() throws IOException {
		System.out.println("executing end-to-end tests.");
		PrintStream stdout = System.out;
		InputStream stdin = System.in;
		
		ByteArrayOutputStream actual_output = new ByteArrayOutputStream();
		System.setOut(new PrintStream(actual_output));
		ByteArrayInputStream input = new ByteArrayInputStream("john 3 0".getBytes());
		System.setIn(input);
		SampleProgram.main(new String[] {});
		assertEquals("Adding user \"john\".\nfaculty user John added.\n", actual_output.toString());
		
		actual_output = new ByteArrayOutputStream();
		System.setOut(new PrintStream(actual_output));
		SampleProgram.main(new String[] {"John", "0", "5"});
		assertEquals("Adding user \"John\".\nadding user failed. \r\n", actual_output.toString());
		
		System.setOut(stdout);
		System.setIn(stdin);
		System.out.println("end-to-end testing finished.");
	}

}
