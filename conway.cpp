#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

int Rows = 200;
int Cols = 200;
int chance = 25;
bool corners = true;
int respawn = 3;
int overpopulation = 3;
int underpopulation = 2;

std::vector<std::vector<uint8_t>> grid;
std::vector<std::vector<int>> gridi;

float width, height;
int i;

bool run = false;
bool settings = true;

sf::Font font("Arial.TTF");
sf::Text RowsT(font);
sf::Text ColsT(font);
sf::Text chanceT(font);
sf::Text cornersT(font);
sf::Text respawnT(font);
sf::Text overpopulationT(font);
sf::Text underpopulationT(font);
sf::Text resetT(font);
sf::Text infoT(font);

void conway(){
    for (auto& i : gridi)
        std::fill(i.begin(), i.end(), 0);
    if(corners){
        for(int row=0; row < Rows; row++){
            for(int col=0; col < Cols; col++){
                if(grid[row][col]){
                    gridi[(row+1)%Rows][col]++;
                    gridi[(row+1)%Rows][(col+1)%Cols]++;
                    gridi[(row+(Rows-1))%Rows][col]++;
                    gridi[(row+(Rows-1))%Rows][(col+(Cols-1))%Cols]++;
                    gridi[row][(col+1)%Cols]++;
                    gridi[(row+(Rows-1))%Rows][(col+1)%Cols]++;
                    gridi[row][(col+(Cols-1))%Cols]++;
                    gridi[(row+1)%Rows][(col+(Cols-1))%Cols]++;
                }
            }
        }
    }else{
        for(int row=0; row < Rows; row++){
            for(int col=0; col < Cols; col++){
                if(grid[row][col]){
                    gridi[(row+1)%Rows][col]++;
                    gridi[(row+(Rows-1))%Rows][col]++;
                    gridi[row][(col+1)%Cols]++;
                    gridi[row][(col+(Cols-1))%Cols]++;
                }
            }
        }
    }
    for(int row=0; row < Rows; row++){
        for(int col=0; col < Cols; col++){
            if(gridi[row][col]==respawn && !grid[row][col])
                grid[row][col] = true;
            else if(gridi[row][col]>overpopulation && grid[row][col])
                grid[row][col] = false;
            else if(gridi[row][col]<underpopulation && grid[row][col])
                grid[row][col] = false;
        }
    }
}

void randStart(){
    for(int i=0; i < Rows; i++){
        for(int j=0; j < Cols; j++){
            grid[i][j]=rand()%101 < chance;
        }
    }
}

void clear(){
    for (auto& i : grid)
        std::fill(i.begin(), i.end(), 0);
}

void fill(){
    for (auto& i : grid)
        std::fill(i.begin(), i.end(), 1);
}

void reset(){
    Rows = 200;
    Cols = 200;
    chance = 25;
    corners = true;
    respawn = 3;
    overpopulation = 3;
    underpopulation = 2;

    RowsT.setString("Rows: " + std::to_string(Rows));
    ColsT.setString("Cols: " + std::to_string(Cols));
    chanceT.setString("Chance: " + std::to_string(chance));
    cornersT.setString("Corners: " + std::string(corners ? "On" : "Off"));
    respawnT.setString("Respawn: " + std::to_string(respawn));
    overpopulationT.setString("Overpopulation: " + std::to_string(overpopulation));
    underpopulationT.setString("Underpopulation: " + std::to_string(underpopulation));

    grid = std::vector<std::vector<uint8_t>>(Rows, std::vector<uint8_t>(Cols, 0));
    gridi = std::vector<std::vector<int>>(Rows,std::vector<int>(Cols, 0));
}

int main(){

    grid = std::vector<std::vector<uint8_t>>(Rows, std::vector<uint8_t>(Cols, 0));
    gridi = std::vector<std::vector<int>>(Rows,std::vector<int>(Cols, 0));

    sf::RenderWindow window(sf::VideoMode({800, 600}), "My window");
    window.setVerticalSyncEnabled(true);

    RowsT.setString("Rows: " + std::to_string(Rows));
    ColsT.setString("Cols: " + std::to_string(Cols));
    chanceT.setString("Chance: " + std::to_string(chance));
    cornersT.setString("Corners: " + std::string(corners ? "On" : "Off"));
    respawnT.setString("Respawn: " + std::to_string(respawn));
    overpopulationT.setString("Overpopulation: " + std::to_string(overpopulation));
    underpopulationT.setString("Underpopulation: " + std::to_string(underpopulation));
    resetT.setString("Reset Settings");
    infoT.setString(" Space: Play/Pause \n Right: Step \n R: Random \n C: Clear \n F: Fill \n Esc: Settings");

    randStart();

    while (window.isOpen()){

        height = window.getSize().y/float(Rows);
        width = window.getSize().x/float(Cols);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            //ajustes
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                    settings = !settings;
                    run = false;
                }

            //pausar
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                if (keyPressed->scancode == sf::Keyboard::Scancode::Space && !settings)
                    run = !run;
            
            //un paso
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                if (keyPressed->scancode == sf::Keyboard::Scancode::Right)
                    conway();

            //random fill
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                if (keyPressed->scancode == sf::Keyboard::Scancode::R)
                    randStart();

            //clear
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                if (keyPressed->scancode == sf::Keyboard::Scancode::C)
                    clear();

            //fill
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                if (keyPressed->scancode == sf::Keyboard::Scancode::F)
                    fill();

            //resize correcto
            if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                sf::Vector2f pos(0.f, 0.f);
                sf::Vector2f size(
                    static_cast<float>(resized->size.x),
                    static_cast<float>(resized->size.y)
                );

                sf::FloatRect visibleArea(pos, size);
                window.setView(sf::View(visibleArea));
            }

            //cell dead/alive
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
                if (mouseButtonPressed->button == sf::Mouse::Button::Left){
                    if(!settings){
                        int c = mouseButtonPressed->position.x / width;
                        int r = mouseButtonPressed->position.y / height;
                        grid[r][c] = !grid[r][c];
                    }
                    if(settings){
                        sf::Vector2f pos(mouseButtonPressed->position.x, mouseButtonPressed->position.y);
                        if(cornersT.getGlobalBounds().contains(pos)){
                            corners = !corners;
                            cornersT.setString("Corners: " + std::string(corners ? "On" : "Off"));
                            if(!corners){
                                if(respawn > 4){
                                    respawn = 4;
                                    respawnT.setString("Respawn: " + std::to_string(respawn));
                                }
                                if(overpopulation > 4){
                                    overpopulation = 4;
                                    overpopulationT.setString("Overpopulation: " + std::to_string(overpopulation));
                                }
                                if(underpopulation > 4){
                                    underpopulation = 4;
                                    underpopulationT.setString("Underpopulation: " + std::to_string(underpopulation));
                                }
                            }
                        }
                        if(resetT.getGlobalBounds().contains(pos)) reset();
                    }
                }
            if (const auto* mouseWheel = event->getIf<sf::Event::MouseWheelScrolled>())
                if (mouseWheel->wheel == sf::Mouse::Wheel::Vertical){
                    sf::Vector2f pos(mouseWheel->position.x, mouseWheel->position.y);

                    if(chanceT.getGlobalBounds().contains(pos)){
                        chance += mouseWheel->delta;
                        if(chance < 0) chance = 0;
                        if(chance > 100) chance = 100;
                        chanceT.setString("Chance: " + std::to_string(chance));
                    }

                    if(RowsT.getGlobalBounds().contains(pos)){
                        Rows += mouseWheel->delta;
                        if(Rows < 1) Rows = 1;
                        RowsT.setString("Rows: " + std::to_string(Rows));
                        grid = std::vector<std::vector<uint8_t>>(Rows, std::vector<uint8_t>(Cols, 0));
                        gridi = std::vector<std::vector<int>>(Rows,std::vector<int>(Cols, 0));
                    }

                    if(ColsT.getGlobalBounds().contains(pos)){
                        Cols += mouseWheel->delta;
                        if(Cols < 1) Cols = 1;
                        ColsT.setString("Cols: " + std::to_string(Cols));
                        grid = std::vector<std::vector<uint8_t>>(Rows, std::vector<uint8_t>(Cols, 0));
                        gridi = std::vector<std::vector<int>>(Rows,std::vector<int>(Cols, 0));
                    }

                    if(respawnT.getGlobalBounds().contains(pos)){
                        respawn += mouseWheel->delta;
                        if(respawn < 0) respawn = 0;
                        if(corners) if(respawn > 8) respawn = 8;
                        if(!corners) if(respawn > 4) respawn = 4;
                        respawnT.setString("Respawn: " + std::to_string(respawn));
                    }

                    if(overpopulationT.getGlobalBounds().contains(pos)){
                        overpopulation += mouseWheel->delta;
                        if(overpopulation < 0) overpopulation = 0;
                        if(corners) if(overpopulation > 8) overpopulation = 8;
                        if(!corners) if(overpopulation > 4) overpopulation = 4;
                        overpopulationT.setString("Overpopulation: " + std::to_string(overpopulation));
                    }

                    if(underpopulationT.getGlobalBounds().contains(pos)){
                        underpopulation += mouseWheel->delta;
                        if(underpopulation < 0) underpopulation = 0;
                        if(corners) if(underpopulation > 8) underpopulation = 8;
                        if(!corners) if(underpopulation > 4) underpopulation = 4;
                        underpopulationT.setString("Underpopulation: " + std::to_string(underpopulation));
                    }
                }
        }

        if(run)conway();
        
        window.clear();

        for(int row=0; row < Rows; row++){
            for(int col=0; col < Cols; col++){
                if(grid[row][col]){
                    sf::RectangleShape cell(sf::Vector2f(width, height));

                    cell.setPosition(sf::Vector2f(col * width, row * height));

                    cell.setFillColor(sf::Color::White);
                    window.draw(cell);
                }
            }
        }

        if(settings){
            sf::RectangleShape cell(sf::Vector2f(window.getSize().x, window.getSize().y));
            cell.setPosition(sf::Vector2f(0,0));
            cell.setFillColor(sf::Color(50, 50, 50, 200));
            window.draw(cell);

            RowsT.setPosition(sf::Vector2f(10, 10));
            ColsT.setPosition(sf::Vector2f(10, 40));
            chanceT.setPosition(sf::Vector2f(10, 70));
            cornersT.setPosition(sf::Vector2f(10, 100));
            respawnT.setPosition(sf::Vector2f(10, 130));
            overpopulationT.setPosition(sf::Vector2f(10, 160));
            underpopulationT.setPosition(sf::Vector2f(10, 190));
            resetT.setPosition(sf::Vector2f(10, 230));
            infoT.setPosition(sf::Vector2f(10, 260));

            window.draw(RowsT);
            window.draw(ColsT);
            window.draw(chanceT);
            window.draw(cornersT);
            window.draw(respawnT);
            window.draw(overpopulationT);
            window.draw(underpopulationT);
            window.draw(resetT);
            window.draw(infoT);

        }

        window.display(); 
    }
    
}