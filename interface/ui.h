#ifndef UI_H_
#define UI_H_

enum CrossoverMethod { SEQUENTIAL = 0, RANDOM = 1 };
enum SelectionMethod { TRUNCATION = 0, ROULETTE = 1, RANK = 2, ELITIST_REPLACEMENT = 3, HYBRID = 4 };

class UI
{
public:
    // Chart
    static void AddFitnessStats(double best, double worst, double avg);
    static void ClearFitnessChart();

    // Canvas
    static void ClearCanvas();
    static void DrawBasePoint(double x, double y);
    static void DrawIndividual(double x, double y);
    static void DrawBestIndividual(double x, double y);
    static void DrawWorstIndividual(double x, double y);

    // Config getters
    static int    CrossoverRate();
    static int    MutationRate();
    static int    PopulationSize();
    static int    MaxGenerations();
    static int    MaxX();
    static int    MaxY();
    static int    MinX();
    static int    MinY();
    static int    BasePointCount();
    static double DistanceFactor();
    static double DistributionFactor();
    static int    CanvasWidth();
    static int    CanvasHeight();

    static void UpdateDisplay();

    static CrossoverMethod GetCrossoverMethod();
    static SelectionMethod GetSelectionMethod();

    // Commands
    static void InitializeApp();
    static void GeneratePopulationAuto();
    static void GeneratePopulationManual();
    static void RunOneGeneration();
    static void RunTenGenerations();
    static void RunHundredGenerations();
    static void RunAllGenerations();
    static void GenerateBasePoints();

private:
    UI();
};

#endif /* UI_H_ */
