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

	// Clé permettant de coder le mot de passe
	private final int pass_key[] = { 147, 6479, 12345, 7842, 66, 177, 253, 122, 9548, 1215, 48421, 629, 314, 4784, 5102,
			914, 213, 316, 145, 78 };

	private final String passFile;
	private String password;
	private final String defaultPassword = "admin";

	public Password(String path) {
		this.passFile = path;
		this.password = this.load();
	}

	// Chiffre une chaine de caractère en utilisant le codage par l'opération
	// XOR
	private String xor(String in) {
		String out = "";
		for (int i = 0; i < in.length(); i += 1) {
			out += (char) (in.charAt(i) ^ this.pass_key[i]);
		}
		return out;
	}

	// Charge le mot de passe chiffré
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
			e.printStackTrace();
		} catch (IOException e) {
			this.reset();
			out = this.password;
		} catch (Exception e) {
			e.printStackTrace();
		}
		return this.xor(out);

	}

	// Change le mot de passe
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

	// Reset le mot de passe à sa valeur par défaut
	public void reset() {
		this.change(this.defaultPassword);
	}

	// Compare un mot de passe à un autre
	public boolean compare(String password) {
		return this.password.equals(password);
	}
}
