import javax.swing.*;
import java.awt.*;
import java.util.Base64;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GUI extends JFrame implements ActionListener {

    private JLabel label1, label2, label3, label4;
    private JTextField plainTextField, keyTextField, chiperTextField, decryptedTextField;
    private JButton EncryptButton, DecryptButton;
    private byte[] cipherText; //parameter to save the encrypted text
    private Boolean isDecrypted = false; //parameter to if decrypted

    public GUI() {
        //set the title and size of the frame
        setTitle("Data Encryption Standard");
        setSize(500, 250);
        Font font = new Font("Arial", Font.BOLD, 16);

        //create the labels
        label1 = new JLabel("Plain Text:");
        label1.setFont(font);
        label1.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 10));
        label2 = new JLabel("Key:");
        label2.setFont(font);
        label2.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 10));
        label3 = new JLabel("Cipher Text:");
        label3.setFont(font);
        label4 = new JLabel("Decrypted Text:");
        label4.setFont(font);
        
        //create the text fields
        plainTextField = new JTextField(10);
        plainTextField.setFont(font);
        keyTextField = new JTextField(10);
        keyTextField.setFont(font);
        chiperTextField = new JTextField(10);
        chiperTextField.setEditable(false);
        chiperTextField.setFont(font);
        decryptedTextField = new JTextField(10);
        decryptedTextField.setEditable(false);
        decryptedTextField.setFont(font);
        //create the buttons
        EncryptButton = new JButton("Encrypt");
        EncryptButton.addActionListener(this);
        DecryptButton = new JButton("Decrypt");
        DecryptButton.addActionListener(this);

        //blank labels for gapping
        JLabel blankLabel1 = new JLabel();
        blankLabel1.setPreferredSize(new Dimension(0, 10)); 
        JLabel blankLabel2 = new JLabel();
        blankLabel2.setPreferredSize(new Dimension(0, 10)); 
 
        //create a panel to hold the labels and text fields
        JPanel panel = new JPanel(new GridLayout(5, 2));
        panel.add(label1);
        panel.add(plainTextField);
        panel.add(label2);
        panel.add(keyTextField);
        panel.add(blankLabel1);
        panel.add(blankLabel2);
        panel.add(label3);
        panel.add(chiperTextField);
        panel.add(label4);
        panel.add(decryptedTextField);
        panel.setBorder(BorderFactory.createEmptyBorder(10, 60, 10, 60));

        //create a panel to hold the buttons
        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        buttonPanel.add(EncryptButton);
        buttonPanel.add(DecryptButton);

        //add the panels to the frame
        Container contentPane = getContentPane();
        contentPane.add(panel, BorderLayout.CENTER);
        contentPane.add(buttonPanel, BorderLayout.SOUTH);
    }
    
    //handels the press of buttons
    public void actionPerformed(ActionEvent e) { 
        String text = this.plainTextField.getText();
        String key = this.keyTextField.getText();

        if(e.getSource() == this.EncryptButton){ //if Encrypt button pressed
            isDecrypted = false;// set parameter to false 
            if(text.isEmpty() || key.isEmpty()){ //if fields are empty
                JOptionPane.showMessageDialog(null,
                    "Fields are empty!", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }
            else if(text.length() != 8 || key.length() != 8){ //if we get invalid length
                JOptionPane.showMessageDialog(null,
                    "Plaintext and key must be 8 characters!", "Length Error", JOptionPane.ERROR_MESSAGE);
                return;
            }
            cipherText = DES.DESFunction(text.getBytes(), key.getBytes(), false); //call our DES function
            this.decryptedTextField.setText(""); //sets the decrypted text field to ""
            this.chiperTextField.setText(Base64.getEncoder().encodeToString(cipherText)); //sets the output in the cipher text field

            //prints the keys of the encryption
            byte[][] keys = DES.KeySchedule(key.getBytes(), false);
            System.out.println("Keys:");
            for (byte[] row : keys) {
                for (byte b : row) {
                    String binaryString = String.format("%8s", Integer.toBinaryString(b & 0xFF)).replace(' ', '0');
                    System.out.print(binaryString + " ");
                }
                System.out.println();
            }
        }
        
        if(e.getSource() == this.DecryptButton){ //if Decrypt button pressed
            if(isDecrypted == true){ //check we decrypted already
                JOptionPane.showMessageDialog(null,
                    "You already decrypted!", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }
            if(this.chiperTextField.getText().isEmpty()){ //checks if we didnt encrypt 
                JOptionPane.showMessageDialog(null,
                    "You must encrypt first!", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }
            isDecrypted = true; //set the parameter to tell we decrypted
            byte[] decrypted = DES.DESFunction(cipherText, key.getBytes(), true); //calls DES function with cipherText and key
            this.decryptedTextField.setText(new String(decrypted)); //sets the decrypted text in the text field
        }
    }

    public static void main(String[] args) {
        //create the frame and show it
        GUI frame = new GUI();
        //get the screen size
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();

        //calculate the new location of the frame
        int x = (int) ((screenSize.getWidth() - frame.getWidth()) / 2);
        int y = (int) ((screenSize.getHeight() - frame.getHeight()) / 2);

        //set the location of the frame
        frame.setLocation(x, y);
        frame.setVisible(true);
        //closes the window when we exit
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}