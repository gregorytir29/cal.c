#include <stdio.h>
#include <stdlib.h>


int dim[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//Array of Days in Month
char *monthnames[]= {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};//Array of Month Names

int get_dow(int day, int month, int year){

        /*(for general use, outside of the cal program)
          int dim[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
          dim[1] += (y < 1752) ? (y % 4 == 0)
          : (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)); //Checking for a Leap Year 
        */

        if (year<=0 || month<1 || month>12 || day<1 || day>31 || day > dim[month-1]) { //Invalid dates
                return 0;
        }else{
                if(month == 1 || month == 2){//if Month = Jan or Feb
                        month += 12;
                        year --;
                }
                
                if (year < 1752 || (year == 1752 && month < 9) || (year == 1752 && month == 9 && day <= 2)) {  // Julian Check
                                int dow = (day + (13 * (month + 1)) / 5 + year + year / 4 + 5) % 7; //(1)
                                return (dow == 0) ? 7 : dow; // Return 7 for Saturday
                } else if (year > 1752 || (year == 1752 && month > 9) || (year == 1752 && month == 9 && day >= 14)) {   // Gregorian Check
                                int dow = (day + (13 * (month + 1)) / 5 + year + year / 4 - year / 100 + year / 400) % 7; //(2)
                                return (dow == 0) ? 7 : dow; // Return 7 for Saturday 
                }                      
                        return 0;  // Invalid dates during calendar transition

        }
        
}

int IsItLeap(int y) {
    // Julian rules for years < 1752, Gregorian rules otherwise (counts 1752 as a Leap Year)
    return (y < 1752) ? (y % 4 == 0)
         : (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
}


void printmonth(int month, int year){
        
        printf("\t %s\n", monthnames[month-1]);//print month name
                
        printf("Su Mo Tu We Th Fr Sa \n");
        
        int startingday = get_dow(1,month,year);

                for (int gapcount = 1; gapcount < startingday; gapcount++) { //gaps before days start
                        printf("   ");
                }

        if (month == 9 && year==1752){//Case for September 1752
                
                for (int day=1; day<=dim[month-1]; day++){
                        printf("%2d ",day);
                        if (day==2) day = 13; //day skip of sept 1752
                        if ((startingday + day + 2)%7==0) printf("\n"); //line break when week ends (+2 because of day skip)
                }

        }else{
                for (int day=1; day<=dim[month-1]; day++){
                        printf("%2d ",day);
                        if ((startingday + day - 1) % 7 == 0) printf("\n"); //line break when week ends
                }
        }
        printf("\n");
}
               
int print3months(int m2, int year) {
    #define max_weeks 6
    int week, weekdaypos;
    int septcount=1; //Count for September 1752

    //Print Month and Day names
    printf("\t %s\t\t\t\b%s\t\t\t\b\b\b%s\t\n",monthnames[m2],monthnames[m2+1],monthnames[m2+2]);
    printf("Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa  Su Mo Tu We Th Fr Sa \n");

    // Loop through each week
    for (week = 0; week < max_weeks; week++) {
        //Loop through each month
        for (int monthcount = 0; monthcount < 3; monthcount++) {
            // Print days for each month
            for (weekdaypos = 0; weekdaypos < 7; weekdaypos++) {
                //int current_week = week * 7
                //int current_day_position = weekdaypos - (get_dow(1,m2+monthcount+1,year)-1) + 1
                int current_day = week * 7 + weekdaypos - (get_dow(1,m2+monthcount+1,year)-1) + 1; // = current_week + current_day_position
                
                if (year == 1752 && m2+monthcount==8){ //Special 1752 September Case
                        if (septcount < 31){
                                if (septcount == 1)printf("      ");
                                printf("%2d ",septcount);
                                septcount++;
                                if (septcount==3)septcount=14;
                                if (septcount == 17)break; // (Goto line 106 --> 109)
                        }             
                }else if ( current_day > 0 && current_day <= dim[m2+monthcount]) { //All other cases
                    printf("%2d ", current_day);
                } else {
                    printf("   "); // Empty space for days outside the month's range
                }
            }
            printf(" "); // Space between months
        }
        printf("\n");
    }

    return 0;
}

void printyear(int y){
        
        printf("\t\t\t\t\b\b%d\n",y);//Year Header

        for(int starting_month=0; starting_month<12; starting_month+=3){ //Print Three Months for Four Columns.

                print3months(starting_month,y);
                printf("\n");
        }
}

int main(){

        printf("Welcome to the calendar!\nYear:");
        int res, m, y, w;
        res = scanf("%d",&y); //User Input

                if (res != 1 || y<=0){ //User Input Check
                        printf("Invalid input of Year (Year has to be Positive). Please try again!\n");
                        exit(1);
                 }

                printf("Month (0 to print entire year):");

        res = scanf("%d",&m); // -//-

                if (res != 1 || m>12 || m<0){ // -//-
                        printf("Invalid input of Month (Month has to be between 0-12). Please try again!\n");
                        exit(1);
                }
        
        dim[1] += IsItLeap(y);//Checking for a Leap Year

        if (m==0) printyear(y); //Prints the requested Year
        else printmonth(m,y); //Print the singular, User-Requested Month.
        return 0;
}
