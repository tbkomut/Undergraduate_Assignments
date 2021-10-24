package ConnectFour;

import javax.swing.*;
import java.awt.*;

public class ConnectFour extends JFrame {

    private int size;
    private char game_type;
    private JFrame item;

    public int getterSize(){
        return size;
    }

    public char getterGame(){
        return game_type;
    }

    public JFrame getterFrame(){
        return item;
    }

    /**
     * The function to start the game. The game type is selected here.
     */
    public void startingToGame(JFrame item)throws Exception{
        int status;
        String size=null;
        int sizeOfBoard=0;
        JOptionPane.showMessageDialog(item,"Please you enter size of the board to will be created.\nHint: Size can be an even number from 4 to 20.");
        do {
            status=0;
            try {
                size = JOptionPane.showInputDialog(item, "Please enter size of board:");
                sizeOfBoard = Integer.parseInt(size);
                if (sizeOfBoard < 4 || sizeOfBoard > 20 || sizeOfBoard % 2 == 1) {
                    JOptionPane.showMessageDialog(item, "The board size can be an even number from 4 to 20.", "Invalid size number.", JOptionPane.ERROR_MESSAGE);
                }
                else status=1;
            }
            catch(NumberFormatException e){
                if(size==null) {
                    int state = JOptionPane.showConfirmDialog(item, "Do you want to close game?", "Game", JOptionPane.YES_NO_OPTION);
                    if (state == JOptionPane.YES_OPTION)
                        System.exit(0);
                }
                else{
                    JOptionPane.showMessageDialog(item, "The board size can be an even number from 4 to 20.", "Invalid size", JOptionPane.ERROR_MESSAGE);
                }
            }
            catch(Exception e){
                System.out.println(e.toString());
                JOptionPane.showMessageDialog(item, "The board size can be an even number from 4 to 20.", "Size isn't a number.", JOptionPane.ERROR_MESSAGE);
            }
        }while(status==0);
        this.size=sizeOfBoard;
    }

    /**
     * 	Is the game against the computer or against an user?
     */
    public void typeOfGame(JFrame item){
        char type;
        int status;
        do {
            status = 0;
            String typeOption=JOptionPane.showInputDialog(item,"Which game type will you play?\nPress C to play against a computer.\nPress P to play against a player2.");
            type=typeOption.charAt(0);
            if ((type != 'C' && type != 'c') && (type != 'P' && type != 'p')) {
                status = 1;
                JOptionPane.showMessageDialog(item,"Game type can be C or P","Invalid game type",JOptionPane.ERROR_MESSAGE);
            }
        } while (status == 1);
        game_type=type;
    }

    public void Component()throws Exception{
        item= new JFrame("Connect Four Game");
        item.setLayout( new FlowLayout() );
        item.add(new JLabel(new ImageIcon("Connect_Four.gif")));
        item.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        item.setSize(400, 500);
        item.setVisible(true);
        startingToGame(item);
        typeOfGame(item);
    }

    public static void main(String args[]){
        ConnectFour game=new ConnectFour();
        try {
            game.Component();
            char type = game.getterGame();
            int size = game.getterSize();
            game.getterFrame().setVisible(false);
            if (type == 'C' || type == 'c') {
                ConnectFourGame game1 = new ConnectFour_AI(size, type);
                GuiGame guigame = new GuiGame(game1, size);
            } else {
                ConnectFourGame game1 = new ConnectFour_User(size, type);
                GuiGame guigame = new GuiGame(game1, size);
            }
        }
        catch (Exception e) {
            System.out.println("Board size can be a number");
            System.exit(0);
        }
    }
}
