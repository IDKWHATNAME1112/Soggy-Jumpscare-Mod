#include <geode/geode.hpp>
#include <geode/modify/PlayerObject.hpp>
#include <cocos2d.h>

using namespace geode::prelude;

class $modify(PlayerObject) {
    bool pushButton(PlayerButton button) {
        bool result = PlayerObject::pushButton(button);
        if (button == PlayerButton::Jump && PlayLayer::get()) {
            showImageAndSound();
        }
        return result;
    }

    void showImageAndSound() {
        auto scene = cocos2d::CCDirector::sharedDirector()->getRunningScene();
        if (!scene) return;

        auto image = cocos2d::CCSprite::create("sog.png"_spr);
        if (!image) return;

        auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
        float scaleX = winSize.width / image->getContentSize().width;
        float scaleY = winSize.height / image->getContentSize().height;

        image->setScaleX(scaleX);
        image->setScaleY(scaleY);
        image->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        image->setOpacity(255);

        scene->addChild(image, 1000);

        std::string soundPath = (Mod::get()->getResourcesDir() / "boom.mp3").string();
        FMODAudioEngine::sharedEngine()->playEffect(soundPath);

        image->runAction(
            cocos2d::CCSequence::create(
                cocos2d::CCFadeIn::create(0.05f),
                cocos2d::CCFadeOut::create(0.2f),
                cocos2d::CCRemoveSelf::create(),
                nullptr
            )
        );
    }
};