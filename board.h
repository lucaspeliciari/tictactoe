class Board 
{
    public:
        char tiles[3][3];
        bool playing = true;
        Board()
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    tiles[i][j] = ' ';
                }
            }
        }
};