package model.entities;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.List;

public class Password {

	private final int pass_key[] = { 147, 6479, 12345, 7842, 66, 177, 253, 122, 9548, 1215, 48421, 629, 314, 4784, 5102,
			914, 213, 316, 145, 78 };

	private final String passFile = "../bin/.pass";
	private String password;
	private final String defaultPassword = "admin";

	public Password() {
		this.password = this.load();
	}

	private String xor(String in) {
		String out = "";
		for (int i = 0; i < in.length(); i += 1) {

			// System.out.println(in.charAt(i%in.length()) ^ this.pass_key[i]);
			out += (char) (in.charAt(i) ^ this.pass_key[i]);
		}
		return out;
	}

	private String load() {
		String out = null;
		String line = null;
		try {

			File fileDir = new File(this.passFile);

			BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream(fileDir), "UTF8"));

			while ((line = in.readLine()) != null) {
				out = line;
			}

			in.close();
		} catch (UnsupportedEncodingException e) {
			System.out.println(e.getMessage());
		} catch (IOException e) {
			this.reset();
			out = this.password;
		} catch (Exception e) {
			System.out.println(e.getMessage());
		}
		System.out.println(out);
		return this.xor(out);

	}

	public void change(String password) {
		this.password = password;
		List<String> lines = Arrays.asList(this.xor(password));
		Path file = Paths.get(this.passFile);
		try {
			Files.write(file, lines, Charset.forName("UTF-8"));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void reset() {
		this.change(this.defaultPassword);
	}

	public boolean compare(String password) {
		return this.password.equals(password);
	}

	public static void main(String[] args) {
		Password password = new Password();
		System.out.println(password.xor("admin"));
		password.change("cgbregd");
		System.out.println(password.password);
	}
}
