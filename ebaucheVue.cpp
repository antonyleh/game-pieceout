#include <SFML/Graphics.hpp>
#include <iostream>
#include "Model/GameModel.hpp"
#include "Controller/GameController.hpp"

enum class GameState {
    MENU,
    GAME
};

bool isPivot(std::shared_ptr<PieceConcrete> pc, int gx, int gy)
{
    if(!pc || pc->getCoordinates().empty()) return false;
    auto pivot = pc->getCoordinates()[0];
    return (pivot.first == gx && pivot.second == gy);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "Piece Out");
    window.setFramerateLimit(60);

    GameModel model;
    GameController controller(model);
    GameState state = GameState::MENU;

    sf::Texture bgTexture;
    bgTexture.loadFromFile("./Utility/background.png");
    sf::Sprite bgSprite(bgTexture);
    bgSprite.setScale(
       800.f / bgTexture.getSize().x,
       600.f / bgTexture.getSize().y);

    sf::Font fontTitle;
    fontTitle.loadFromFile("./Utility/arial.otf");
    sf::Text txtTitle("Piece Out", fontTitle, 50); 
    txtTitle.setFillColor(sf::Color::White);
    sf::FloatRect trect = txtTitle.getLocalBounds();
    txtTitle.setOrigin(trect.width/2.f, 0.f);
    txtTitle.setPosition(400.f, 30.f);

    sf::Texture tex1, tex2, tex3, tex4;
    tex1.loadFromFile("./Utility/level1.png");
    tex2.loadFromFile("./Utility/level2.png");
    tex3.loadFromFile("./Utility/level3.png");
    tex4.loadFromFile("./Utility/level4.png");
    sf::Sprite sp1(tex1), sp2(tex2), sp3(tex3), sp4(tex4);
    sp1.setScale(0.25f,0.25f);  sp1.setPosition(150.f,180.f);
    sp2.setScale(0.25f,0.25f);  sp2.setPosition(450.f,140.f);
    sp3.setScale(0.25f,0.25f);  sp3.setPosition(150.f,350.f);
    sp4.setScale(0.25f,0.25f);  sp4.setPosition(480.f,350.f);

    sf::Texture texArrowUp, texArrowDown, texArrowLeft, texArrowRight, texRotate;
    texArrowUp.loadFromFile("./Utility/arrowUp.png");
    texArrowDown.loadFromFile("./Utility/arrowDown.png");
    texArrowLeft.loadFromFile("./Utility/arrowLeft.png");
    texArrowRight.loadFromFile("./Utility/arrowRight.png");
    texRotate.loadFromFile("./Utility/rotate.png");

    int tileSize = 64;
    int nbCols=0, nbRows=0;
    int marginLeft=0, marginTop=0;

    sf::RectangleShape btnUndo(sf::Vector2f(60.f,30.f));
    btnUndo.setPosition(10.f,555.f);
    btnUndo.setFillColor(sf::Color(200,50,50));

    sf::Font font;
    font.loadFromFile("./Utility/arial.otf");
    sf::Text txtUndo("Annuler", font, 25);
    txtUndo.setFillColor(sf::Color::White);
    sf::FloatRect tb = txtUndo.getLocalBounds();
    txtUndo.setOrigin(tb.width/2.f, tb.height/2.f);
    txtUndo.setPosition(btnUndo.getPosition().x + 30.f,
                        btnUndo.getPosition().y + 10.f);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed) {
                window.close();
            }
            if(event.type==sf::Event::KeyPressed
               && event.key.code==sf::Keyboard::Escape)
            {
                if(state==GameState::GAME) state=GameState::MENU;
                else window.close();
            }
            if(state==GameState::MENU)
            {
                if(event.type==sf::Event::MouseButtonPressed
                   && event.mouseButton.button==sf::Mouse::Left)
                {
                    sf::Vector2f mpf((float)sf::Mouse::getPosition(window).x,
                                     (float)sf::Mouse::getPosition(window).y);
                    if(sp1.getGlobalBounds().contains(mpf)){
                        model.initLevel1(); state=GameState::GAME;
                        nbCols=6; nbRows=1;
                        marginLeft=(800 - nbCols*tileSize)/2;
                        marginTop =(600 - nbRows*tileSize)/2;
                    }
                    else if(sp2.getGlobalBounds().contains(mpf)){
                        model.initLevel2(); state=GameState::GAME;
                        nbCols=5; nbRows=5;
                        marginLeft=(800 - nbCols*tileSize)/2;
                        marginTop =(600 - nbRows*tileSize)/2;
                    }
                    else if(sp3.getGlobalBounds().contains(mpf)){
                        model.initLevel3(); state=GameState::GAME;
                        nbCols=3; nbRows=7;
                        marginLeft=(800 - nbCols*tileSize)/2;
                        marginTop =(600 - nbRows*tileSize)/2;
                    }
                    else if(sp4.getGlobalBounds().contains(mpf)){
                        model.initLevel4(); state=GameState::GAME;
                        nbCols=3; nbRows=7;
                        marginLeft=(800 - nbCols*tileSize)/2;
                        marginTop =(600 - nbRows*tileSize)/2;
                    }
                }
            }
            else if(state==GameState::GAME)
            {
                if(event.type==sf::Event::MouseButtonPressed
                   && event.mouseButton.button==sf::Mouse::Left)
                {
                    sf::Vector2i mpos = sf::Mouse::getPosition(window);
                    controller.handleMousePressed(mpos, marginLeft, marginTop, tileSize);
                }
                if(event.type==sf::Event::MouseButtonReleased
                   && event.mouseButton.button==sf::Mouse::Left)
                {
                    sf::Vector2i mpos = sf::Mouse::getPosition(window);
                    controller.handleMouseReleased(mpos, marginLeft, marginTop);
                }
                if(event.type==sf::Event::MouseMoved)
                {
                    sf::Vector2i mpos = sf::Mouse::getPosition(window);
                    controller.handleMouseMoved(mpos, marginLeft, marginTop, tileSize);
                }
            }
        }
        if(state==GameState::GAME) {
            auto &ps = model.getPieces();
            if(!ps.empty()) {
                auto red = std::dynamic_pointer_cast<PieceConcrete>(ps[0]);
                if(red) {
                    for(auto &rc : red->coordinates) {
                        int lvl = model.getLevelNumber();
                        if(lvl==1 && rc.first==5 && rc.second==0) {
                            state=GameState::MENU; break;
                        }
                        else if(lvl==2 && rc.first==2 && rc.second==0){
                            state=GameState::MENU; break;
                        }
                        else if(lvl==3 && rc.first==2 && rc.second==0){
                            state=GameState::MENU; break;
                        }
                        else if(lvl==4 && rc.first==1 && rc.second==0){
                            state=GameState::MENU; break;
                        }
                    }
                }
            }
        }
        window.clear(sf::Color(60,60,60));
        if(state==GameState::MENU) {
            window.draw(bgSprite);
            window.draw(txtTitle);
            window.draw(sp1);
            window.draw(sp2);
            window.draw(sp3);
            window.draw(sp4);
        }
        else if(state==GameState::GAME) {
            for(int y=0; y<nbRows; y++){
                for(int x=0; x<nbCols; x++){
                    if(model.isTileWalkable(x,y)){
                        sf::RectangleShape cell(sf::Vector2f(64.f,64.f));
                        cell.setPosition((float)marginLeft + x*64.f,
                                         (float)marginTop  + y*64.f);
                        cell.setFillColor(sf::Color::White);
                        window.draw(cell);
                    }
                }
            }
            if(model.getLevelNumber()==1){
                sf::RectangleShape pink(sf::Vector2f(64.f,64.f));
                pink.setFillColor(sf::Color(255,128,220));
                pink.setPosition((float)marginLeft+5*64.f,
                                 (float)marginTop);
                window.draw(pink);
            }
            else if(model.getLevelNumber()==2){
                sf::RectangleShape pink(sf::Vector2f(64.f,64.f));
                pink.setFillColor(sf::Color(255,128,220));
                pink.setPosition((float)marginLeft+2*64.f,
                                 (float)marginTop);
                window.draw(pink);
            }
            else if(model.getLevelNumber()==3){
                sf::RectangleShape pink(sf::Vector2f(64.f,64.f));
                pink.setFillColor(sf::Color(255,128,220));
                pink.setPosition((float)marginLeft+2*64.f,
                                 (float)marginTop);
                window.draw(pink);
            }
            else if(model.getLevelNumber()==4){
                sf::RectangleShape pink(sf::Vector2f(64.f,64.f));
                pink.setFillColor(sf::Color(255,128,220));
                pink.setPosition((float)marginLeft+1*64.f,
                                 (float)marginTop);
                window.draw(pink);
            }
            window.draw(btnUndo);
            window.draw(txtUndo);
            float arrowScale=0.05f;
            auto &ps=model.getPieces();
            for(size_t i=0;i<ps.size();i++){
                auto pc=std::dynamic_pointer_cast<PieceConcrete>(ps[i]);
                if(!pc) continue;
                sf::Color col = pc->getColor();
                for(auto &c : pc->coordinates){
                    sf::RectangleShape block(sf::Vector2f(64.f,64.f));
                    block.setPosition((float)marginLeft + c.first*64.f,
                                      (float)marginTop  + c.second*64.f);
                    block.setFillColor(col);
                    window.draw(block);
                }
                if(pc->coordinates.empty()) continue;
                if(pc->canRotate && pc->showRotateIcon){
                    auto pivot=pc->coordinates[0];
                    sf::Sprite sRot(texRotate);
                    sRot.setScale(arrowScale,arrowScale);
                    sRot.setOrigin(sRot.getLocalBounds().width/2.f,
                                   sRot.getLocalBounds().height/2.f);
                    sRot.setPosition((float)marginLeft + pivot.first*64.f+32.f,
                                     (float)marginTop  + pivot.second*64.f+32.f);
                    window.draw(sRot);
                }
                if(!pc->hasArrows) continue;
                auto pivot=pc->coordinates[0];
                float px=(float)marginLeft + pivot.first*64.f + 32.f;
                float py=(float)marginTop  + pivot.second*64.f + 32.f;
                if (pc->orientation == 0) {
                    auto leftMost = *std::min_element(
                        pc->coordinates.begin(), pc->coordinates.end(),
                        [](const Position &a, const Position &b) {
                            return a.first < b.first;
                        });
                    auto rightMost = *std::max_element(
                        pc->coordinates.begin(), pc->coordinates.end(),
                        [](const Position &a, const Position &b) {
                            return a.first < b.first;
                        });
                    sf::Sprite sLeft(texArrowLeft);
                    sLeft.setScale(arrowScale, arrowScale);
                    sLeft.setOrigin(sLeft.getLocalBounds().width / 2.f, sLeft.getLocalBounds().height / 2.f);
                    sLeft.setPosition(
                        (float)marginLeft + leftMost.first * 64.f + 16.f,  
                        (float)marginTop + leftMost.second * 64.f + 32.f);
                    window.draw(sLeft);
                    sf::Sprite sRight(texArrowRight);
                    sRight.setScale(arrowScale, arrowScale);
                    sRight.setOrigin(sRight.getLocalBounds().width / 2.f, sRight.getLocalBounds().height / 2.f);
                    sRight.setPosition(
                        (float)marginLeft + rightMost.first * 64.f + 48.f, 
                        (float)marginTop + rightMost.second * 64.f + 32.f);
                    window.draw(sRight);
                }
                    else if (pc->orientation == 1) { 
                    auto topMost = *std::min_element(
                        pc->coordinates.begin(), pc->coordinates.end(),
                        [](const Position &a, const Position &b) {
                            return a.second < b.second;
                        });
                    auto bottomMost = *std::max_element(
                        pc->coordinates.begin(), pc->coordinates.end(),
                        [](const Position &a, const Position &b) {
                            return a.second < b.second;
                        });
                    sf::Sprite sUp(texArrowUp);
                    sUp.setScale(arrowScale, arrowScale);
                    sUp.setOrigin(sUp.getLocalBounds().width / 2.f, sUp.getLocalBounds().height / 2.f);
                    sUp.setPosition(
                        (float)marginLeft + topMost.first * 64.f + 32.f,   
                        (float)marginTop + topMost.second * 64.f + 16.f); 
                    window.draw(sUp);
                    sf::Sprite sDown(texArrowDown);
                    sDown.setScale(arrowScale, arrowScale);
                    sDown.setOrigin(sDown.getLocalBounds().width / 2.f, sDown.getLocalBounds().height / 2.f);
                    sDown.setPosition(
                        (float)marginLeft + bottomMost.first * 64.f + 32.f,  
                        (float)marginTop + bottomMost.second * 64.f + 48.f); 
                    window.draw(sDown);
                }
                else if(pc->orientation==2){
                    sf::Sprite sUp(texArrowUp);
                    sUp.setScale(arrowScale,arrowScale);
                    sUp.setOrigin(sUp.getLocalBounds().width/2.f,
                                  sUp.getLocalBounds().height/2.f);
                    sUp.setPosition(px, py-20);
                    window.draw(sUp);

                    sf::Sprite sDown(texArrowDown);
                    sDown.setScale(arrowScale,arrowScale);
                    sDown.setOrigin(sDown.getLocalBounds().width/2.f,
                                    sDown.getLocalBounds().height/2.f);
                    sDown.setPosition(px, py+20);
                    window.draw(sDown);

                    sf::Sprite sl(texArrowLeft);
                    sl.setScale(arrowScale,arrowScale);
                    sl.setOrigin(sl.getLocalBounds().width/2.f,
                                 sl.getLocalBounds().height/2.f);
                    sl.setPosition(px-20, py);
                    window.draw(sl);

                    sf::Sprite sr(texArrowRight);
                    sr.setScale(arrowScale,arrowScale);
                    sr.setOrigin(sr.getLocalBounds().width/2.f,
                                 sr.getLocalBounds().height/2.f);
                    sr.setPosition(px+20, py);
                    window.draw(sr);
                }
            }
        }
        window.display();
    }
    return 0;
}
