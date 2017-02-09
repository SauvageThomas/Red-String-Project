package src.view.layout;

import java.util.Optional;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Dialog;
import javafx.scene.control.Label;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuItem;
import javafx.scene.control.PasswordField;
import javafx.scene.control.ButtonBar.ButtonData;
import javafx.scene.layout.GridPane;
import javafx.util.Pair;

public class RootController extends ViewController {

	@FXML
	private Menu menuFile;

	public RootController() {
	}

	@FXML
	private void initialize() {

	}

	@FXML
	private void loginHandler() {
		this.showLoginDialog();
	}

	private void showLoginDialog() {
		// Create the custom dialog.
		Dialog<Pair<String, String>> dialog = new Dialog<>();
		dialog.setTitle("Admin login");
		dialog.setHeaderText("Please, enter the password.");

		// Set the icon (must be included in the project).

		// Set the button types.
		ButtonType loginButtonType = new ButtonType("Login", ButtonData.OK_DONE);
		dialog.getDialogPane().getButtonTypes().addAll(loginButtonType, ButtonType.CANCEL);

		// Create the username and password labels and fields.
		GridPane grid = new GridPane();
		grid.setHgap(10);
		grid.setVgap(10);
		grid.setPadding(new Insets(20, 150, 10, 10));

		PasswordField password = new PasswordField();
		password.setPromptText("Password");

		grid.add(new Label("Password :"), 0, 0);
		grid.add(password, 1, 0);

		// Enable/Disable login button depending on whether a password was
		// entered.
		Node loginButton = dialog.getDialogPane().lookupButton(loginButtonType);
		loginButton.setDisable(true);

		// Do some validation (using the Java 8 lambda syntax).
		password.textProperty().addListener((observable, oldValue, newValue) -> {
			loginButton.setDisable(newValue.trim().isEmpty());
		});

		dialog.getDialogPane().setContent(grid);

		// Convert the result to a username-password-pair when the login button
		// is clicked.
		dialog.setResultConverter(dialogButton -> {
			if (dialogButton == loginButtonType) {
				return new Pair<>("admin", password.getText());
			}
			return null;
		});

		Platform.runLater(() -> password.requestFocus());

		dialog.initOwner(this.main.getPrimaryStage());
		Optional<Pair<String, String>> result = dialog.showAndWait();

		result.ifPresent(usernamePassword -> {
			// TODO: Test if the password is correct
			System.out.println("Username=" + usernamePassword.getKey() + ", Password=" + usernamePassword.getValue());
			this.main.activeAdminMode();
		});
	}

	public void displayAdminMode() {
		for (MenuItem m : this.menuFile.getItems()) {
			m.setVisible(true);
		}
	}

}
