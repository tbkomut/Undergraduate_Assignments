package ConnectFour;

import javax.swing.*;
import java.util.Random;

public class ConnectFour_AI extends ConnectFourGame {
    private int row[];

    public ConnectFour_AI(){

    }

    public ConnectFour_AI(int size,char type){
        super(size,type);
    }

    public void playGame(JPanel tag,JButton items[]){
        playWithComputer(tag,items);
    }

    /**
     * It performs commands to play against the computer.
     */
    void playWithComputer(JPanel tag,JButton items[]){
        int count=0;
        Character input;
        char gamer;
        int row = 0;
        int[] column={0};
        int status;
        int condition=0;
        int returnValue;
        char step;

        do{
            if(count%2==1){
                gamer='O';			/* COMPUTER	*/
                moveOfComputer(column);
                step= (char) ('A'+column[0]);
//                System.out.println("Computer: " + step);
            }
            else{
                do{
                    status=0;
                    input=getInputs("Player's move",tag);
                    if(legalPosition(input)==0){
                        status=1;
                        JOptionPane.showMessageDialog(tag,"This column is full or invalid.","Warning!",JOptionPane.ERROR_MESSAGE);
                    }
                }while(status==1);
                gamer='X';			/* USER	*/
                column[0]=input-'a';
            }
            row=assignToBoard(column,gamer);
            returnValue=gameStatus(row,column,gamer);
            if(returnValue==1 || returnValue==2)	condition=1;
            if(condition==0);	assignToGUI(tag,items,row,column[0],gamer);
            if(condition==1 && returnValue==1){
                assignToGUI(tag,items,row,column[0], (char) (gamer+('a'-'A')));
                if(count%2==0)
                    JOptionPane.showMessageDialog(tag,"The player won the game.");
                else
                    JOptionPane.showMessageDialog(tag,"The computer won the game.");
            }
            else if(condition==1 && returnValue==2){
                JOptionPane.showMessageDialog(tag,"The game ended in a draw.");
            }
            count++;
        }while(condition==0);
//        displayBoard();
    }

    /**
     * It supplies the computer player to make its basic moves.
     * @param column
     */
    void moveOfComputer(int column[]){
        int i,j;
        int status;
        row=new int[board.length];
        /*	row [i] is the number of empty rows in a column. i is the i th column. */
        for(i=0;i<board.length;++i){
            for(j=0,status=0;j<board.length && status==0;++j){
                if(board[j][i]!='.')	status=1;
            }
            if(status==1)	row[i]=j-1;
            else 			row[i]=j;
        }

        if(searchFourList(row,column,'O')==0){
            if(blockEnemyList(row,column,'X')==0){
                makeList(row,column,'O');
            }
        }

    }

    /**
     * For the next move, the computer player moves when the game is over.
     * @param row
     * @param column
     * @param gamer
     * @return
     */
    int searchFourList(int row[],int column[],char gamer){
        int i;
        int reset=0;
        column[0]=0;
        for(i=0,reset=0;i<board.length && reset==0;++i){
            if(legalPosition((char) ('a'+i))==1){
                board[row[i]-1][i]=gamer;
                if(diagonalControl(row[i]-1,i,gamer,1)==4){
                    reset++;
                    column[0]=i;
                }
                if(verticalControl(row[i]-1,i,gamer,1)==4){
                    reset++;
                    column[0]=i;
                }
                if(horizontalControl(row[i]-1,i,gamer,1)==4){
                    reset++;
                    column[0]=i;
                }
                board[row[i]-1][i]='.';
            }
        }

        return reset;
    }

    /**
     * If User can finish the game for next move .It allows user's next move is blocked.
     * @param row
     * @param column
     * @param gamer
     * @return
     */
    int blockEnemyList(int row[],int column[],char gamer){
        int i;
        int block=0;
        column[0]=0;
        for(i=0,block=0;i<board.length && block==0;++i){
            if(legalPosition((char) ('a'+i))==1){
                board[row[i]-1][i]=gamer;
                if(diagonalControl(row[i]-1,i,gamer,1)==4){
                    block++;
                    column[0]=i;
                }
                if(verticalControl(row[i]-1,i,gamer,1)==4){
                    block++;
                    column[0]=i;
                }
                if(horizontalControl(row[i]-1,i,gamer,1)==4){
                    block++;
                    column[0]=i;
                }
                board[row[i]-1][i]='.';
            }
        }

        return block;
    }

    /**
     * If the game is not over for the next move, It tries to create a long list for computer.
     * @param row
     * @param column
     * @param gamer
     */
    void makeList(int row[],int column[],char gamer){
        int i,j;
        int[] maxNumber=new int[BOARD_SIZE];
        int step1,step2,step3;
        int max=0;
        int reset;
        int random;

        for(i=0;i<board.length;++i){
            if(legalPosition((char) ('a'+i))==1){
                step1=diagonalControl(row[i]-1,i,gamer,1);
                step2=verticalControl(row[i]-1,i,gamer,1);
                step3=horizontalControl(row[i]-1,i,gamer,1);
                if(step1>max)	max=step1;
                if(step2>max)	max=step2;
                if(step3>max)	max=step3;
            }
        }

        for(i=0,j=0;i<board.length;++i){
            if(legalPosition((char) ('a'+i))==1){
                step1=diagonalControl(row[i]-1,i,gamer,1);
                step2=verticalControl(row[i]-1,i,gamer,1);
                step3=horizontalControl(row[i]-1,i,gamer,1);
                if((step1==max || step2==max || step3==max)){
                    maxNumber[j++]=i;
                }
            }
        }

        if(j!=0){
            Random rand = new Random();
            random = rand.nextInt(j);
        }
        else{
            random=0;
        }

        column[0]=maxNumber[random];
    }

}
