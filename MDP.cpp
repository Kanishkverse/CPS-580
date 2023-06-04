//
//  MDP.cpp
//  AI_GridWorld
//

//
// PROJECT SUBMITTED BY KANISHKVERSE CPS 580 - 2022 SUMMER
// please find the video of working model, iterations end at 24.00 steps
#include <stdio.h>

#include "MDP.h"


/*************************************************************** Below are the two functions you need to implement ****************************************************/


/*Compute a Q-value for a given state and its action
  Input: state variable s; action (go to East/North/West/South), the corresponding interger value for each action is defined in the "MDP.h" Macros definition on the top
  Output: you need to update the corresponding q_values of the input state variable s
 */
void MDP::computeQValue(State &s, const int action)
{
    // define containers for each direction, namely first, second and third
    double fq, seq, tq;
    
    double frate = 0.499; // this for fail rate of transition fail. it ratio of fail transition divide into half. which is 0.5. for absolute value I used 0.499 so that policy will have fuzzy values like in real world scenario.
    double tf = TRANSITION_FAIL;
    double ts = TRANSITION_SUCCEED;
    double ga = GAMMA;
    double ar = ACTION_REWARD;

    /*East, West, North, South to Q values are calculated here with conditionals*/
    if (action == ACTION_EAST)
    {
        
        if (s.location.x == 0 && s.location.y == 1) // when robot faces the wall
        {
            seq = ts*(ar + ga*states[s.location.y][s.location.x].state_value); fq = tf*frate*(ar + ga*states[0][0].state_value);
            tq = tf*frate*(ar + ga*states[2][0].state_value);
            double sumof = (seq + fq + tq);
           // calculating convergence
            if (cur_convergence < abs(s.q_values[0] - sumof))
                cur_convergence = abs(s.q_values[0] - sumof);
            s.q_values[0] = sumof;
        }
        else
        {
            if (s.location.y == 2)
            {
                // moving to south
                fq = tf*frate*(ar + ga*states[s.location.y][s.location.x].state_value);
            }
            else
            {
                if ((s.location.y  == 0) && (s.location.x == 1))
                {
                    // wall
                    fq = tf*frate*(ar + ga*states[s.location.y][s.location.x].state_value);
                }
                else
                {
                   // else go south
                    fq = tf*frate*(ar + ga*states[s.location.y + 1][s.location.x].state_value);
                }
            }
            if (s.location.x == 3)
            {
                // x value facing wall
                seq = ts*(ar + ga*states[s.location.y][s.location.x].state_value);
            }
            else
            {
                if (s.location.y == 1 && s.location.x == 0)
                {
                    // when action is east and face wall
                    seq = ts*(ar + ga*states[s.location.y][s.location.x].state_value);
                }
                else
                {
                    //take east action by adding 1
                    seq = ts*(ar + ga*states[s.location.y][s.location.x + 1].state_value);
                }
            }
            if (s.location.y == 0)
            {
                // action north
                tq = tf*frate*(ar + ga*states[s.location.y][s.location.x].state_value);
            }
            else
            {
                if (s.location.y == 2 && s.location.x == 1)
                {
                    // if its north and wall
                    tq = tf*frate*(ar + ga*states[s.location.y][s.location.x].state_value);
                }
                else
                {
                    // move to north
                    tq = tf*frate*(ar + ga*states[s.location.y - 1][s.location.x].state_value);
                }
            }
            double sumof = (seq + fq + tq);
            // calculating the convergence for east
            if (cur_convergence < abs(s.q_values[0] - sumof))
                cur_convergence = abs(s.q_values[0] - sumof);
            s.q_values[0] = sumof;
        }
    }
    else if (action == ACTION_WEST) // Action when to take WEST
    {
        //at the wall
        if (s.location.x == 2 && s.location.y == 1)
        {
            
            fq = tf*frate*(ar + ga*states[s.location.y - 1][s.location.x].state_value);
            seq = ts*(ar + ga*states[s.location.y][s.location.x].state_value);
            tq = tf*frate*(ar + ga*states[s.location.y + 1][s.location.x].state_value);
            double sumof = (seq + fq + tq);
            // calculating convergence
            if (cur_convergence < abs(s.q_values[2] - sumof))
                cur_convergence = abs(s.q_values[2] - sumof);
            s.q_values[2] = sumof;
        }
        else
        {
            
            if (s.location.y == 2)
            {
                fq = tf*frate*(ar + ga*states[s.location.y][s.location.x].state_value);
            }
            else
            {
                /*face the wall situation*/
                if (s.location.y == 0 && s.location.x == 1)
                {
                    fq = tf*frate*(ar + ga*states[s.location.y][s.location.x].state_value);
                }
                else
                {
                    fq = tf*frate*(ar + ga*states[s.location.y + 1][s.location.x].state_value);
                }
            }
            
            if (s.location.x == 0)
            {
                seq = ts*(ar + ga*states[s.location.y][s.location.x].state_value);
            }
            else
            {
                if (s.location.y == 1 && s.location.x == 2)
                {
                    
                    seq = ts*(ar + ga*states[s.location.y][s.location.x].state_value);
                }
                else
                {
                    seq = ts*(ar + ga*states[s.location.y][s.location.x - 1].state_value);
                }
            }
            // move to north
            if (s.location.y == 0)
            {
                tq = tf*frate*(ar + ga*states[s.location.y][s.location.x].state_value);
            }
            else
            {
                if (s.location.y == 2 && s.location.x == 1)
                {
                    //wall
                    tq = tf*frate*(ar + ga*states[s.location.y][s.location.x].state_value);
                }
                else
                {
                    tq = tf*frate*(ar + ga*states[s.location.y - 1][s.location.x].state_value);
                }
            }
            double sumof = (seq + fq + tq);
           // convergence
            if (cur_convergence < abs(s.q_values[2] - sumof))
                cur_convergence = abs(s.q_values[2] - sumof);
            s.q_values[2] = sumof;
        
        }
    }

    else if (action == ACTION_NORTH)
    {
        // hit the wall
        if (s.location.x == 1 && s.location.y == 2)
        {
            fq = tf*frate*(ar + ga*states[s.location.y ][s.location.x- 1].state_value);
            seq = ts*(ar + ga*states[s.location.y][s.location.x].state_value);
            tq = tf*frate*(ar + ga*states[s.location.y ][s.location.x+ 1].state_value);
            double sumof = (seq + fq + tq);
            
            if (cur_convergence < abs(s.q_values[3] - sumof))
                cur_convergence = abs(s.q_values[3] - sumof);
            s.q_values[3] = sumof;
        }
        else
        {
            // move left
            if (s.location.x == 0)
            {
                fq = tf*frate*(ar + ga*states[s.location.y][s.location.x].state_value);
            }
            else
            {
                // go west when hit the wall
                if (s.location.y == 1 && s.location.x == 2)
                {
                    fq = tf*frate*(ar + ga*states[s.location.y][s.location.x].state_value);
                }
                else
                {
                    fq = tf*frate*(ar + ga*states[s.location.y][s.location.x - 1].state_value);
                }
            }
            // go upwards
            if (s.location.y == 0)
            {
                seq = ts*(ar + ga*states[s.location.y][s.location.x].state_value);
            }
            else
            {
                if (s.location.y == 2 && s.location.x == 1)
                {
                    // when wall is faced to robot
                    seq = ts*(ar + ga*states[s.location.y][s.location.x].state_value);
                }
                else
                {
                    seq = ts*(ar + ga*states[s.location.y - 1][s.location.x].state_value);
                }
            }
            // east
            if (s.location.x == 3)
            {
                tq = tf*frate*(ar + ga*states[s.location.y][s.location.x].state_value);
            }
            else
            {
                if (s.location.y == 1 && s.location.x == 0)
                {
                    tq = tf*frate*(ar + ga*states[s.location.y][s.location.x].state_value);
                }
                else
                {
                    tq = tf*frate*(ar + ga*states[s.location.y][s.location.x + 1].state_value);
                }
            }
            double sumof = (seq + fq + tq);
            // convergence calculation
            if (cur_convergence < abs(s.q_values[3] - sumof))
                cur_convergence = abs(s.q_values[3] - sumof);
            s.q_values[3] = sumof;
            
        }
    }

    else
    {
        // but when wall is faced move to south
        if (s.location.x == 1 && s.location.y == 0)
        {
            fq = tf*frate*(ar + ga*states[s.location.y][s.location.x - 1].state_value);
            seq = ts*(ar + ga*states[s.location.y][s.location.x].state_value);
            tq = tf*frate*(ar + ga*states[s.location.y][s.location.x + 1].state_value);
            double sumof = (seq + fq + tq);
            //convergence to above values
            if (cur_convergence < abs(s.q_values[1] - sumof))
                cur_convergence = abs(s.q_values[1] - sumof);
            s.q_values[1] = sumof;
        }
        else
        {
            // when to move lft or west
            if (s.location.x == 0)
            {
                fq = tf*frate*(ar + ga*states[s.location.y][s.location.x].state_value);
            }
            else
            {
                if (s.location.y == 1 && s.location.x == 2)
                {
                    fq = tf*frate*(ar + ga*states[s.location.y][s.location.x].state_value);
                }
                else
                {
                    fq = tf*frate*(ar + ga*states[s.location.y][s.location.x - 1].state_value);
                }
            }
            // move south
            if (s.location.y == 2)
            {
                seq = ts*(ar + ga*states[s.location.y][s.location.x].state_value);
            }
            else
            {
                if (s.location.y == 0 && s.location.x == 1)
                {
                    seq = ts*(ar + ga*states[s.location.y][s.location.x].state_value);
                }
                else
                {
                    seq = ts*(ar + ga*states[s.location.y + 1][s.location.x].state_value);
                }
            }
            //move east
            if (s.location.x == 3)
            {
                tq = tf*frate*(ar + ga*states[s.location.y][s.location.x].state_value);
            }
            else
            {
                if (s.location.y == 1 && s.location.x == 0)
                {
                    tq = tf*frate*(ar + ga*states[s.location.y][s.location.x].state_value);
                }
                else
                {
                    tq = tf*frate*(ar + ga*states[s.location.y][s.location.x + 1].state_value);
                }
            }
            double sumof = (seq + fq + tq); // adding 3 q direction values into one
            
            if (cur_convergence < abs(s.q_values[1] - sumof))
                cur_convergence = abs(s.q_values[1] - sumof);
            s.q_values[1] = sumof;
        }
    }
}


/*There is no return value, actually you need to use the computing result to update the state values of all the states defined as data member "State states[3][4]". Of course, you don't need to update the wall state: states[1][1], the diamond state: states[0][3], and pitfall state: states[1][3] */
void MDP::valueIteration()
{
    // keeping current convergence to 0
    cur_convergence = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((i == 1 && j == 1) ||
             (i == 0 && j == 3) ||
              (i == 1&&j == 3))
                continue;
            else
            {
                double et = ACTION_EAST;
                double st = ACTION_SOUTH;
                double wt = ACTION_WEST;
                double nt = ACTION_NORTH;
                // four actions and every state
                computeQValue(states[i][j], et); computeQValue(states[i][j], st);
                computeQValue(states[i][j], wt); computeQValue(states[i][j], nt);

            }
        }
    }
    // value of states with q values getting max of it
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((i == 1 && j == 1) ||
                (i == 0 && j == 3) ||
                (i == 1 && j == 3))
                continue;
            else
            {
                float a1 = states[i][j].q_values[0];
                float b1 =states[i][j].q_values[1];
                float c1 = states[i][j].q_values[2];
                float d1 = states[i][j].q_values[3];
                //q_values[0] corresponds to action East; 
                //q_values[1] corresponds to action South; 
                //q_values[2] corresponds to action West; 
                //q_values[3] corresponds to action North
                float a2 = max(a1,b1); // max of east n south
                float b2 = max(a2,c1); // max of a2 and west
                
                states[i][j].state_value = max(b2,d1); // finally max of b2 and north
            }
        }
    }
}
/**********************************************************************    End of Assignment *********************************************************************/



/**********************************************************************    End of Assignment *********************************************************************/





MDP::MDP()
{
    /*Initialize all the state with 0.0 state_value and 0.0 Q_values*/
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            states[y][x].location.x = x; //specify the location for this state
            states[y][x].location.y = y;
            
            states[y][x].state_value = 0.0; //define the state value
            states[y][x].q_values[0] = 0.0; //define the Q value
            states[y][x].q_values[1] = 0.0;
            states[y][x].q_values[2] = 0.0;
            states[y][x].q_values[3] = 0.0;
        }
    }
    
    /* Reset the values for the two special states: diamonds (0, 3), pitfall (1, 3). Actually there are no Q-values for these two states as these two states represents the final state of the game. Similarly, for the wall (1, 1), it does not have any state value or Q values. So make sure not to update these three states during your program*/
    states[0][3].state_value = 1.0;
    states[1][3].state_value = -1.0;
    
    
    
    /*Set the current convergence to a big number initially*/
    cur_convergence = 100; //the reason this value is set to a big value is to ensure
    
    
}


MDP::~MDP()
{
    
}

/*Reset the current computed state and Q values*/
void MDP::resetData()
{
    /*Initialize all the state with 0.0 state_value and 0.0 Q_values*/
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            states[y][x].location.x = x; //specify the location for this state
            states[y][x].location.y = y;
            
            states[y][x].state_value = 0.0; //define the state value
            states[y][x].q_values[0] = 0.0; //define the Q value
            states[y][x].q_values[1] = 0.0;
            states[y][x].q_values[2] = 0.0;
            states[y][x].q_values[3] = 0.0;
        }
    }
    
    /* Reset the values for the two special states: diamonds (0, 3), pitfall (1, 3). Actually there are no Q-values for these two states as these two states represents the final state of the game. Similarly, for the wall (1, 1), it does not have any state value or Q values. So make sure not to update these three states during your program*/
    states[0][3].state_value = 1.0;
    states[1][3].state_value = -1.0;
    
    
    
    /*Set the current convergence to a big number initially*/
    cur_convergence = 100; //the reason this value is set to a big value is to ensure
    
    
}
