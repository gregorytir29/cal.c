# cal.c
A simple command-line LLD calendar generator written in C, supporting both Julian and Gregorian calendars — including the historical September 1752 calendar transition with the missing days.
The calendar is printed in a 3x4 yearly table or a particular month is printed, based off user input.

 Program Overview – cal.c

The program begins by prompting the user to input a year and a month. After verifying that the inputs are valid, it determines whether the given year is a leap year, making the appropriate adjustment to February’s number of days.

Depending on the user's input:

    If the month is 0, the program calls the PrintYear() function to display the entire year, grouped in 3-month sections.

    If a specific month (1–12) is given, the program calls the PrintMonth() function to display that single month day by day.

📘 Function Breakdown

    PrintMonth(int month, int year)
    Accepts the month and year as arguments and prints the corresponding calendar month, aligned by week. A newline is inserted after every Saturday to start a new week. Includes special handling for September 1752 (the historical calendar transition month), skipping days 3–13.

    PrintYear(int year)
    Accepts the year and prints all twelve months by calling Print3Months() four times (for each quarter). Each row consists of three months printed side-by-side, week-by-week.

    Print3Months(int startMonth, int year)
    Prints a block of three consecutive months in a horizontal format. It loops through six weeks and aligns days accordingly. Special care is taken for September 1752.

    get_dow(int day, int month, int year)
    Calculates the day of the week for a given date using Zeller’s Congruence, accounting for both Julian and Gregorian calendars. Dates before 14 September 1752 follow the Julian rules; later dates follow Gregorian. Invalid dates during the calendar transition (3–13 September 1752) return 0.

📝 Notes

    Although get_dow() is used internally by the calendar program, it’s written in a way that can be adapted for general-purpose use. However, it currently depends on:

        A global array dim[] (number of days in each month), and

        The leap year adjustment, which is done in main().

    For standalone use, sample code for handling these dependencies is included as comments inside the get_dow() function.
