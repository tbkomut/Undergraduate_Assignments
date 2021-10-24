package ConnectFour;

import javax.swing.*;
import java.awt.*;


public abstract class ConnectFourGame extends JFrame implements UserInterface{

    protected char[][] board;
    protected char game_type;

    public ConnectFourGame(){

    }

    public ConnectFourGame(int sizeOfBoard,char game_type){
        board=new char[sizeOfBoard][sizeOfBoard];
        this.game_type=game_type;
        initBoard();
        //displayBoard();
    }

    public char[][] getterBoard(){
        return board;
    }

    public char getterGameType(){
        return game_type;
    }

    /**
     * This function displays the current board.
     */
    /*
    public void displayBoard(){
        int i,j;
        char chr;
        System.out.print("  ");
        for(i=0;i<board.length;++i){
            chr= (char) ('a'+i);
            System.out.print(chr + " ");
        }
        System.out.println();

        System.out.print("  ");
        for(i=0;i<board.length;++i)
            System.out.print("_ ");
        System.out.println();

        for(i=0;i<board.length;++i){
            System.out.print(" |");
            for(j=0;j<board.length;++j){
                System.out.print(board[i][j]);
                if(j!=board.length-1)	System.out.print(" ");
            }
            System.out.print('|');
            System.out.println();
        }

        System.out.println();
    }
    */
    /**
     * It assigns the initial values of the board.
     */
    private void initBoard(){
        for(int i=0;i<board.length;++i){
            for(int j=0;j<board[i].length;++j)
                board[i][j]='.';
        }
    }

    /**
     * It asks the user to make a move.
     * @return
     */
    protected Character getInputs(String player, JPanel tag){
        int status;
        Character input=null;
        do {
            status = 0;
            try {
                String out = JOptionPane.showInputDialog(player);
                input = out.charAt(0);
                if (input >= 'A' && input <= 'Z') {
                    input = ((char) (input + 32));
                } else if (input >= 'a' && input <= 'z') ;
                else {
                    status = 1;
                    JOptionPane.showMessageDialog(tag, "This column is full or invalid.", "Warning!", JOptionPane.ERROR_MESSAGE);
                }
            }
            catch(StringIndexOutOfBoundsException e){
                status=1;
                JOptionPane.showMessageDialog(tag, "Empty column can not be selected.", "Warning!", JOptionPane.ERROR_MESSAGE);
            }
            catch(NullPointerException e){
                int state = JOptionPane.showConfirmDialog(tag, "Do you want to close game?", "Game",  JOptionPane.YES_NO_OPTION);
                if (state == JOptionPane.YES_OPTION)
                    System.exit(0);
                else
                    status=1;
            }
        }while(status==1);
        return input;
    }

    /**
     * Is the move a legal cell?
     * @param input
     * @return
     */
    protected int legalPosition(Character input){
        int result=0;
        char maxSize= (char) ('a'+ board.length);

        if(input<maxSize && input>='a'){
            result=1;
        }

        if((int)input-'a'<board.length && board[0][((int)input-'a')]!='.'){
            result=0;
        }

        return result;
    }

    /**
     *	It controls the end of the game.If the game ends, it returns 1 or 2.
     * @param row
     * @param column
     * @param gamer
     * @return
     */
    protected int gameStatus(int row,int column[],char gamer){
        int result=0;
        int count;
        int i;
        int diagonal;
        int vertical;
        int horizontal;

        diagonal=diagonalControl(row,column[0],gamer,0);
        vertical=verticalControl(row,column[0],gamer,0);
        horizontal=horizontalControl(row,column[0],gamer,0);

        if(diagonal==4 || horizontal==4 || vertical==4){
            result=1;
        }
        else{
            for(i=0,count=0;i<board.length;++i){
                if(board[0][i]=='.')
                    count++;
            }
            if(count==0)	result=2;
        }

        return result;
    }

    /**
     * It assigns the initial values of the board.
     * @param column
     * @param gamer
     * @return
     */
    protected int assignToBoard(int[] column,char gamer){
        int count=0;
        int index;
        int row=0;

        while(count<board.length && board[count][column[0]]=='.'){
            count++;
        }

        if(count>0 && board[count-1][column[0]]=='.'){
            board[count-1][column[0]]=gamer;
            row=count-1;
        }
        return row;
    }

    /**
     * 	It examines the diagonal list. Returns the longest possible list.
     * @param row
     * @param column
     * @param gamer
     * @param status
     * @return
     */
    protected int diagonalControl(int row,int column,char gamer,int status){
        int i,j,k,r,c;
        int test1,test2;
        int count=0;
        int breakLoop;
        int max1=0,max2=0;
        int max=0;
        int reset;
        int size=board.length;

        /*	Left top-> right bottom diagonal control	*/

        for(i=-3,reset=0;i<=3 && reset==0;++i){
            r=row+i;
            c=column+i;
            if(i<0){
                for(j=0,count=0,breakLoop=0;j<4 && breakLoop==0;++j){
                    if(((r+j>=0) && (r+j<size)) && ((c+j>=0) && (c+j<size))){
                        if(board[r+j][c+j]==gamer)	count++;
                        else breakLoop++;
                    }
                    else breakLoop++;
                }
                if(count>max1)	max1=count;
                if(count==4 && status==0){
                    reset++;
                    for(k=0;k<4;++k)
                        board[r+k][c+k]= (char) (gamer+('a'-'A'));
                }
            }
            else if(i==0){
                for(j=0,test1=0,breakLoop=0;j<4 && breakLoop==0;++j){
                    if(((r+j>=0) && (r+j<size)) && ((c+j>=0) && (c+j<size))){
                        if(board[r+j][c+j]==gamer)	test1++;
                        else breakLoop++;
                    }
                    else breakLoop++;
                }
                for(j=0,test2=0,breakLoop=0;j<4 && breakLoop==0;++j){
                    if(((r-j>=0) && (r-j<size)) && ((c-j>=0) && (c-j<size))){
                        if(board[r-j][c-j]==gamer)	test2++;
                        else breakLoop++;
                    }
                    else breakLoop++;
                }
                if(test1==4  && status==0){
                    reset++;
                    for(k=0;k<4;++k)
                        board[r+k][c+k]= (char) (gamer+('a'-'A'));
                }
                else if(test2==4  && status==0){
                    reset++;
                    for(k=0;k<4;++k)
                        board[r-k][c-k]= (char) (gamer+('a'-'A'));
                }
                if(test1>test2)	count=test1;
                else			count=test2;
                if(count>max1)	max1=count;
            }
            else{
                for(j=0,count=0,breakLoop=0;j<4 && breakLoop==0;++j){
                    if(((r-j>=0) && (r-j<size)) && ((c-j>=0) && (c-j<size))){
                        if(board[r-j][c-j]==gamer)	count++;
                        else breakLoop++;
                    }
                    else breakLoop++;
                }
                if(count>max1)	max1=count;
                if(count==4 && status==0){
                    reset++;
                    for(k=0;k<4;++k)
                        board[r-k][c-k]= (char) (gamer+('a'-'A'));
                }
            }
        }

        /*	Right top -> left bottom diagonal control	*/

        for(i=-3,reset=0;i<=3 && reset==0;++i){
            r=row+i;
            c=column+(-1*i);
            if(i<0){
                for(j=0,count=0,breakLoop=0;j<4 && breakLoop==0;++j){
                    if(((r+j>=0) && (r+j<size)) && ((c-j>=0) && (c-j<size))){
                        if(board[r+j][c-j]==gamer)	count++;
                        else breakLoop++;
                    }
                    else breakLoop++;
                }
                if(count>max2)	max2=count;
                if(count==4 && status==0){
                    reset++;
                    for(k=0;k<4;++k)
                        board[r+k][c-k]= (char) (gamer+('a'-'A'));
                }
            }
            else if(i==0){
                for(j=0,test1=0,breakLoop=0;j<4 && breakLoop==0;++j){
                    if(((r+j>=0) && (r+j<size)) && ((c-j>=0) && (c-j<size))){
                        if(board[r+j][c-j]==gamer)	test1++;
                        else breakLoop++;
                    }
                    else breakLoop++;
                }
                for(j=0,test2=0,breakLoop=0;j<4 && breakLoop==0;++j){
                    if(((r-j>=0) && (r-j<size)) && ((c+j>=0) && (c+j<size))){
                        if(board[r-j][c+j]==gamer)	test2++;
                        else breakLoop++;
                    }
                    else breakLoop++;
                }
                if(test1==4  && status==0){
                    reset++;
                    for(k=0;k<4;++k)
                        board[r+k][c-k]= (char) (gamer+('a'-'A'));
                }
                else if(test2==4  && status==0){
                    reset++;
                    for(k=0;k<4;++k)
                        board[r-k][c+k]= (char) (gamer+('a'-'A'));
                }
                if(test1>test2)	count=test1;
                else			count=test2;
                if(count>max2)	max2=count;
            }
            else{
                for(j=0,count=0,breakLoop=0;j<4 && breakLoop==0;++j){
                    if(((r-j>=0) && (r-j<size)) && ((c+j>=0) && (c+j<size))){
                        if(board[r-j][c+j]==gamer)	count++;
                        else breakLoop++;
                    }
                    else breakLoop++;
                }
                if(count>max2)	max2=count;
                if(count==4 && status==0){
                    reset++;
                    for(k=0;k<4;++k)
                        board[r-k][c+k]= (char) (gamer+('a'-'A'));
                }
            }
        }

        if(max1>=max2)	max=max1;
        else			max=max2;

        return max;
    }

    /**
     *	It examines the vertical list. Returns the longest possible list.
     * @param row
     * @param column
     * @param gamer
     * @param status
     * @return
     */
    protected int verticalControl(int row,int column,char gamer,int status){
        int i,j;
        int count=0;
        int breakLoop=0;

        for(i=row,count=0;i<board.length && i<row+4 && breakLoop==0;++i){
            if(board[i][column]==gamer)	count++;
            else	breakLoop++;
        }
        if(count==4 && status==0)
            for(j=row;j<row+4;++j){
                board[j][column]= (char) (gamer+('a'-'A'));
            }

        return count;
    }

    /**
     * It examines the horizontal list. Returns the longest possible list.
     * @param row
     * @param column
     * @param gamer
     * @param status
     * @return
     */
    protected int horizontalControl(int row,int column,char gamer,int status){
        int i,j,k;
        int breakLoop;
        int count;
        int max=0;

        for(i=column-3;i<=column && i<board.length;++i){
            if(i>=0 && i<=board.length-3){
                for(j=i,count=0,breakLoop=0;j<i+4 && j<board.length && breakLoop==0;++j){
                    if(board[row][j]==gamer)	count++;
                    else	breakLoop++;
                }
                if(max<count)
                    max=count;
                if(count==4 && status==0)
                    for(k=i;k<i+4;++k){
                        board[row][k]= (char) (gamer+('a'-'A'));
                    }
            }
        }

        return max;
    }

    public void assignToGUI(JPanel tag,JButton items[],int row,int column,char player){
        int size=board.length;
        size=(size+1)*size;
        int index=((row+1)*board.length)+column;
        // Removing the panel...
        tag.removeAll();
        // JButton[] replacing...
        items=new JButton[size];
        tag.setLayout( new GridLayout( board.length+1, board.length ) );
        int count=0;
        for(int i=0;i<board.length+1;++i){
            for(int j=0;j<board.length;++j){
                if(i==0){
                    char chr=(char)('A'+j);
                    items[count]=new JButton(String.valueOf(chr));
                    items[count].setBackground(Color.RED);
                }
                else if((i*board.length)+j==index){
                    items[count]=new JButton(String.valueOf(player));
                    items[count].setBackground(Color.BLUE);
                }
                else{
                    items[count] = new JButton(String.valueOf(board[i-1][j]));
                    items[count].setBackground(Color.BLUE);
                }
                tag.add( items[count]);
                count++;
            }
        }
        tag.revalidate();
        tag.repaint();
    }

    /**
     * It is useful for two game mode.
     */
    public abstract void playGame(JPanel tag,JButton items[]);

}
