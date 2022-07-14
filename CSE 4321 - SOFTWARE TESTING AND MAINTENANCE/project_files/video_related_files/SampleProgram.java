package sample;
import java.io.*;
import java.util.ArrayList;

public class SampleProgram {
	static String id_to_name[] = new String[] { "faculty", "student", "admin" };
	static ArrayList<String> super_users = new ArrayList<String>();
	static ArrayList<String> users = new ArrayList<String>();
	
	String capitalize_first_ch(boolean flag, String name) {
		if (!flag) {
			return name;
		}else {
			return name.substring(0, 1).toUpperCase() + name.substring(1);
		}
	}
	
	String[] add_user(String name, int permission_level, int type) {
		try {
			// if first letter of name is not capitalized, capitalize it. 
			boolean need_capitalization = false;
			if (Character.isLowerCase(name.charAt(0))) need_capitalization = true;
			name = capitalize_first_ch(need_capitalization, name);
			
			users.add(name);
			
			if (type == 0 || type == 2 || permission_level == 3) {
				super_users.add(name);
			}
			
			return new String[] {name, id_to_name[type]};
		} catch(ArrayIndexOutOfBoundsException e) {
			return null;
		}
	}

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		String name = null;
		int permission_level;
		int type_id;
		
		if (args.length == 0) {
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			String input = reader.readLine();
			String[] parsed = input.split(" ");
			name = parsed[0]; 
			permission_level = Integer.parseInt(parsed[1]);
			type_id = Integer.parseInt(parsed[2]);
		} else {
			name = args[0];
			permission_level = Integer.parseInt(args[1]);
			type_id = Integer.parseInt(args[2]);
		}
		
		System.out.printf("Adding user \"%s\".\n", name);
		
		SampleProgram instance = new SampleProgram();
		String[] output = instance.add_user(name, permission_level, type_id);
		if (output != null) {
			System.out.printf("%s user %s added.\n", output[1], output[0]);
		} else {
			System.out.println("adding user failed. ");
		}
		
	}
}
