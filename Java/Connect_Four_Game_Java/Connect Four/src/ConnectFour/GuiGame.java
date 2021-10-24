package ConnectFour;

import java.awt.*;
import javax.swing.*;

public class GuiGame extends JFrame{
    private JPanel component[];
    private JButton buttons[];
    private String letters[];
    private int capacity;

    public JPanel getterBoard(){
        return component[0];
    }

    public JButton[] getterValue(){
        return buttons;
    }

    public int getterSize(){
        return capacity;
    }

    public GuiGame(ConnectFourGame game1,int size) {
        super( "Connect Four Game" );
        capacity=size;
        component=new JPanel[3];
        buttons=new JButton[(size+1)*size];
        letters=new String[size];
        for(int i=0;i<3;++i)
            component[i]=new JPanel();
        for(int i=0;i<size;++i) {
            char letter= (char) ('A' + i);
            letters[i] = String.valueOf(letter);
        }
        component[0].setLayout( new GridLayout( size+1, size ) );
        component[1].setLayout( new GridLayout( 1, 1 ) );
        component[2].setLayout( new GridLayout( 1, 1 ) );
        for ( int count = 0; count < (size+1)*size; count++ ) {
            if(count>=size) {
                buttons[count] = new JButton();
                buttons[count].setBackground(Color.BLUE);
            }
            else{
                buttons[count] = new JButton(letters[count]);
                buttons[count].setBackground(Color.RED);
            }
            component[0].add( buttons[count]);
        }
        JButton part1,part2;
        if(game1.getterGameType()=='C' || game1.getterGameType()=='c'){
            part1=new JButton("Player");
            part2=new JButton("Computer");
        }
        else{
            part1=new JButton("Player 1");
            part2=new JButton("Player 2");
        }
        part1.setPreferredSize(new Dimension(100, 500));
        part1.setBackground(Color.ORANGE);
        part2.setPreferredSize(new Dimension(100, 500));
        part2.setBackground(Color.ORANGE);
        component[1].add(part1);
        component[2].add(part2);
        add(component[0],BorderLayout.CENTER);
        add(component[1],BorderLayout.WEST);
        add(component[2],BorderLayout.EAST);
        // Visible GUI
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1300, 700);
        setVisible(true);
        game1.playGame(component[0],buttons);

    }

}