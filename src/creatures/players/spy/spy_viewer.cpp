/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2024 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#include "pch.hpp"

#include "creatures/players/spy/spy_viewer.hpp"

#include "creatures/players/player.hpp"

#include "creatures/interactions/chat.hpp"
#include "config/configmanager.hpp"

#include "server/network/message/outputmessage.hpp"

#include "server/network/protocol/protocolgame.hpp"

SpyViewer::SpyViewer(std::shared_ptr<ProtocolGame> client) :
	m_owner(client) { }

SpyViewer::~SpyViewer() { }

std::shared_ptr<ProtocolGame> SpyViewer::getCastOwner() const {
	return m_owner;
}

void SpyViewer::setCastOwner(std::shared_ptr<ProtocolGame> client) {
	m_owner = client;
}

void SpyViewer::resetCastOwner() {
	m_owner.reset();
}

uint32_t SpyViewer::getViewerId(std::shared_ptr<ProtocolGame> client) const {
	auto it = m_viewers.find(client);
	if (it != m_viewers.end()) {
		return it->second.second;
	}
	return 0;
}

// Inherited
bool SpyViewer::canSee(const Position &pos) const {
	if (m_owner) {
		return m_owner->canSee(pos);
	}

	return false;
}

uint32_t SpyViewer::getIP() const {
	if (m_owner) {
		return m_owner->getIP();
	}

	return 0;
}

void SpyViewer::sendStats() {
	if (m_owner) {
		m_owner->sendStats();

		for (const auto &it : m_viewers) {
			it.first->sendStats();
		}
	}
}

void SpyViewer::sendPing() {
	if (m_owner) {
		m_owner->sendPing();

		for (const auto &it : m_viewers) {
			it.first->sendPing();
		}
	}
}

void SpyViewer::logout(bool displayEffect, bool forceLogout) {
	if (m_owner) {
		m_owner->logout(displayEffect, forceLogout);
	}
}

void SpyViewer::sendAddContainerItem(uint8_t cid, uint16_t slot, std::shared_ptr<Item> item) {
	if (m_owner) {
		m_owner->sendAddContainerItem(cid, slot, item);

		for (const auto &it : m_viewers) {
			it.first->sendAddContainerItem(cid, slot, item);
		}
	}
}

void SpyViewer::sendUpdateContainerItem(uint8_t cid, uint16_t slot, std::shared_ptr<Item> item) {
	if (m_owner) {
		m_owner->sendUpdateContainerItem(cid, slot, item);

		for (const auto &it : m_viewers) {
			it.first->sendUpdateContainerItem(cid, slot, item);
		}
	}
}

void SpyViewer::sendRemoveContainerItem(uint8_t cid, uint16_t slot, std::shared_ptr<Item> lastItem) {
	if (m_owner) {
		m_owner->sendRemoveContainerItem(cid, slot, lastItem);

		for (const auto &it : m_viewers) {
			it.first->sendRemoveContainerItem(cid, slot, lastItem);
		}
	}
}

void SpyViewer::sendUpdatedVIPStatus(uint32_t guid, VipStatus_t newStatus) {
	if (m_owner) {
		m_owner->sendUpdatedVIPStatus(guid, newStatus);

		for (const auto &it : m_viewers) {
			it.first->sendUpdatedVIPStatus(guid, newStatus);
		}
	}
}

void SpyViewer::sendVIP(uint32_t guid, const std::string &name, const std::string &description, uint32_t icon, bool notify, VipStatus_t status) {
	if (m_owner) {
		m_owner->sendVIP(guid, name, description, icon, notify, status);

		for (const auto &it : m_viewers) {
			it.first->sendVIP(guid, name, description, icon, notify, status);
		}
	}
}

void SpyViewer::sendVIPGroups() {
	if (m_owner) {
		m_owner->sendVIPGroups();

		for (const auto &it : m_viewers) {
			it.first->sendVIPGroups();
		}
	}
}

void SpyViewer::sendClosePrivate(uint16_t channelId) {
	if (m_owner) {
		m_owner->sendClosePrivate(channelId);
	}
}

void SpyViewer::sendFYIBox(const std::string &message) {
	if (m_owner) {
		m_owner->sendFYIBox(message);
	}
}

uint32_t SpyViewer::getVersion() const {
	if (m_owner) {
		return m_owner->getVersion();
	}

	return 0;
}

void SpyViewer::disconnect() {
	if (m_owner) {
		m_owner->sendSessionEndInformation(SESSION_END_LOGOUT);
	}
}

void SpyViewer::sendCreatureSkull(std::shared_ptr<Creature> creature) const {
	if (m_owner) {
		m_owner->sendCreatureSkull(creature);

		for (const auto &it : m_viewers) {
			it.first->sendCreatureSkull(creature);
		}
	}
}

void SpyViewer::sendAddTileItem(const Position &pos, uint32_t stackpos, std::shared_ptr<Item> item) {
	if (m_owner) {
		m_owner->sendAddTileItem(pos, stackpos, item);

		for (const auto &it : m_viewers) {
			it.first->sendAddTileItem(pos, stackpos, item);
		}
	}
}

void SpyViewer::sendUpdateTileItem(const Position &pos, uint32_t stackpos, std::shared_ptr<Item> item) {
	if (m_owner) {
		m_owner->sendUpdateTileItem(pos, stackpos, item);

		for (const auto &it : m_viewers) {
			it.first->sendUpdateTileItem(pos, stackpos, item);
		}
	}
}

void SpyViewer::sendRemoveTileThing(const Position &pos, int32_t stackpos) {
	if (m_owner) {
		m_owner->sendRemoveTileThing(pos, stackpos);

		for (const auto &it : m_viewers) {
			it.first->sendRemoveTileThing(pos, stackpos);
		}
	}
}

void SpyViewer::sendUpdateTileCreature(const Position& pos, int32_t stackpos, std::shared_ptr<Creature> creature) {
	if (m_owner) {
		m_owner->sendUpdateTileCreature(pos, stackpos, creature);

		for (const auto& it : m_viewers) {
			it.first->sendUpdateTileCreature(pos, stackpos, creature);
		}
	}
}

void SpyViewer::sendUpdateTile(std::shared_ptr<Tile> tile, const Position &pos) {
	if (m_owner) {
		m_owner->sendUpdateTile(tile, pos);

		for (const auto &it : m_viewers) {
			it.first->sendUpdateTile(tile, pos);
		}
	}
}

void SpyViewer::sendChannelMessage(const std::string &author, const std::string &message, SpeakClasses type, uint16_t channel) {
	if (m_owner) {
		m_owner->sendChannelMessage(author, message, type, channel);

		for (const auto &it : m_viewers) {
			it.first->sendChannelMessage(author, message, type, channel);
		}
	}
}

void SpyViewer::sendMoveCreature(std::shared_ptr<Creature> creature, const Position &newPos, int32_t newStackPos, const Position &oldPos, int32_t oldStackPos, bool teleport) {
	if (m_owner) {
		m_owner->sendMoveCreature(creature, newPos, newStackPos, oldPos, oldStackPos, teleport);

		for (const auto &it : m_viewers) {
			it.first->sendMoveCreature(creature, newPos, newStackPos, oldPos, oldStackPos, teleport);
		}
	}
}

void SpyViewer::sendCreatureTurn(std::shared_ptr<Creature> creature, int32_t stackpos) {
	if (m_owner) {
		m_owner->sendCreatureTurn(creature, stackpos);

		for (const auto &it : m_viewers) {
			it.first->sendCreatureTurn(creature, stackpos);
		}
	}
}

void SpyViewer::sendForgeResult(ForgeAction_t actionType, uint16_t leftItemId, uint8_t leftTier, uint16_t rightItemId, uint8_t rightTier, bool success, uint8_t bonus, uint8_t coreCount, bool convergence) const {
	if (m_owner) {
		m_owner->sendForgeResult(actionType, leftItemId, leftTier, rightItemId, rightTier, success, bonus, coreCount, convergence);
	}
}

void SpyViewer::sendPrivateMessage(std::shared_ptr<Player> speaker, SpeakClasses type, const std::string &text) {
	if (m_owner) {
		m_owner->sendPrivateMessage(speaker, type, text);
	}
}

void SpyViewer::sendCreatureSquare(std::shared_ptr<Creature> creature, SquareColor_t color) {
	if (m_owner) {
		m_owner->sendCreatureSquare(creature, color);

		for (const auto &it : m_viewers) {
			it.first->sendCreatureSquare(creature, color);
		}
	}
}

void SpyViewer::sendCreatureOutfit(std::shared_ptr<Creature> creature, const Outfit_t &outfit) {
	if (m_owner) {
		m_owner->sendCreatureOutfit(creature, outfit);

		for (const auto &it : m_viewers) {
			it.first->sendCreatureOutfit(creature, outfit);
		}
	}
}

void SpyViewer::sendCreatureLight(std::shared_ptr<Creature> creature) {
	if (m_owner) {
		m_owner->sendCreatureLight(creature);

		for (const auto &it : m_viewers) {
			it.first->sendCreatureLight(creature);
		}
	}
}

void SpyViewer::sendCreatureWalkthrough(std::shared_ptr<Creature> creature, bool walkthrough) {
	if (m_owner) {
		m_owner->sendCreatureWalkthrough(creature, walkthrough);

		for (const auto &it : m_viewers) {
			it.first->sendCreatureWalkthrough(creature, walkthrough);
		}
	}
}

void SpyViewer::sendCreatureShield(std::shared_ptr<Creature> creature) {
	if (m_owner) {
		m_owner->sendCreatureShield(creature);

		for (const auto &it : m_viewers) {
			it.first->sendCreatureShield(creature);
		}
	}
}

void SpyViewer::sendContainer(uint8_t cid, std::shared_ptr<Container> container, bool hasParent, uint16_t firstIndex) {
	if (m_owner) {
		m_owner->sendContainer(cid, container, hasParent, firstIndex);

		for (const auto &it : m_viewers) {
			it.first->sendContainer(cid, container, hasParent, firstIndex);
		}
	}
}

void SpyViewer::sendInventoryItem(Slots_t slot, std::shared_ptr<Item> item) {
	if (m_owner) {
		m_owner->sendInventoryItem(slot, item);

		for (const auto &it : m_viewers) {
			it.first->sendInventoryItem(slot, item);
		}
	}
}

void SpyViewer::sendCancelMessage(const std::string &msg) const {
	if (m_owner) {
		m_owner->sendTextMessage(TextMessage(MESSAGE_FAILURE, msg));

		for (const auto &it : m_viewers) {
			it.first->sendTextMessage(TextMessage(MESSAGE_FAILURE, msg));
		}
	}
}

void SpyViewer::sendCancelTarget() const {
	if (m_owner) {
		m_owner->sendCancelTarget();

		for (const auto &it : m_viewers) {
			it.first->sendCancelTarget();
		}
	}
}

void SpyViewer::sendCancelWalk() const {
	if (m_owner) {
		m_owner->sendCancelWalk();

		for (const auto &it : m_viewers) {
			it.first->sendCancelWalk();
		}
	}
}

void SpyViewer::sendChangeSpeed(std::shared_ptr<Creature> creature, uint32_t newSpeed) const {
	if (m_owner) {
		m_owner->sendChangeSpeed(creature, newSpeed);

		for (const auto &it : m_viewers) {
			it.first->sendChangeSpeed(creature, newSpeed);
		}
	}
}

void SpyViewer::sendCreatureHealth(std::shared_ptr<Creature> creature) const {
	if (m_owner) {
		m_owner->sendCreatureHealth(creature);

		for (const auto &it : m_viewers) {
			it.first->sendCreatureHealth(creature);
		}
	}
}

void SpyViewer::sendDistanceShoot(const Position &from, const Position &to, unsigned char type) const {
	if (m_owner) {
		m_owner->sendDistanceShoot(from, to, type);

		for (const auto &it : m_viewers) {
			it.first->sendDistanceShoot(from, to, type);
		}
	}
}

void SpyViewer::sendCreatePrivateChannel(uint16_t channelId, const std::string &channelName) {
	if (m_owner) {
		m_owner->sendCreatePrivateChannel(channelId, channelName);
	}
}

void SpyViewer::sendIcons(uint32_t icons) const {
	if (m_owner) {
		m_owner->sendIcons(icons);

		for (const auto &it : m_viewers) {
			it.first->sendIcons(icons);
		}
	}
}

void SpyViewer::sendMagicEffect(const Position &pos, uint16_t type) const {
	if (m_owner) {
		m_owner->sendMagicEffect(pos, type);

		for (const auto &it : m_viewers) {
			it.first->sendMagicEffect(pos, type);
		}
	}
}

void SpyViewer::sendSkills() const {
	if (m_owner) {
		m_owner->sendSkills();

		for (const auto &it : m_viewers) {
			it.first->sendSkills();
		}
	}
}

void SpyViewer::sendTextMessage(MessageClasses mclass, const std::string &message) {
	if (m_owner) {
		m_owner->sendTextMessage(TextMessage(mclass, message));

		for (const auto &it : m_viewers) {
			it.first->sendTextMessage(TextMessage(mclass, message));
		}
	}
}

void SpyViewer::sendTextMessage(const TextMessage &message) const {
	if (m_owner) {
		m_owner->sendTextMessage(message);

		for (const auto &it : m_viewers) {
			it.first->sendTextMessage(message);
		}
	}
}

void SpyViewer::sendReLoginWindow(uint8_t unfairFightReduction) {
	if (m_owner) {
		m_owner->sendReLoginWindow(unfairFightReduction);
	}
}

void SpyViewer::sendTextWindow(uint32_t windowTextId, std::shared_ptr<Item> item, uint16_t maxlen, bool canWrite) const {
	if (m_owner) {
		m_owner->sendTextWindow(windowTextId, item, maxlen, canWrite);
	}
}

void SpyViewer::sendTextWindow(uint32_t windowTextId, uint32_t itemId, const std::string &text) const {
	if (m_owner) {
		m_owner->sendTextWindow(windowTextId, itemId, text);
	}
}

void SpyViewer::sendToChannel(std::shared_ptr<Creature> creature, SpeakClasses type, const std::string &text, uint16_t channelId) {
	if (m_owner) {
		m_owner->sendToChannel(creature, type, text, channelId);
		for (const auto &it : m_viewers) {
			it.first->sendToChannel(creature, type, text, channelId);
		}
	}
}

void SpyViewer::sendShop(std::shared_ptr<Npc> npc) const {
	if (m_owner) {
		m_owner->sendShop(npc);
	}
}

void SpyViewer::sendSaleItemList(const std::vector<ShopBlock> &shopVector, const std::map<uint16_t, uint16_t> &inventoryMap) {
	if (m_owner) {
		m_owner->sendSaleItemList(shopVector, inventoryMap);
	}
}

void SpyViewer::sendCloseShop() const {
	if (m_owner) {
		m_owner->sendCloseShop();
	}
}

void SpyViewer::sendTradeItemRequest(const std::string &traderName, std::shared_ptr<Item> item, bool ack) const {
	if (m_owner) {
		m_owner->sendTradeItemRequest(traderName, item, ack);
	}
}

void SpyViewer::sendTradeClose() const {
	if (m_owner) {
		m_owner->sendCloseTrade();
	}
}

void SpyViewer::sendWorldLight(const LightInfo &lightInfo) {
	if (m_owner) {
		m_owner->sendWorldLight(lightInfo);

		for (const auto &it : m_viewers) {
			it.first->sendWorldLight(lightInfo);
		}
	}
}

void SpyViewer::sendChannelsDialog() {
	if (m_owner) {
		m_owner->sendChannelsDialog();
	}
}

void SpyViewer::sendOpenPrivateChannel(const std::string &receiver) {
	if (m_owner) {
		m_owner->sendOpenPrivateChannel(receiver);
	}
}

void SpyViewer::sendOutfitWindow() {
	if (m_owner) {
		m_owner->sendOutfitWindow();
	}
}

void SpyViewer::sendCloseContainer(uint8_t cid) {
	if (m_owner) {
		m_owner->sendCloseContainer(cid);

		for (const auto &it : m_viewers) {
			it.first->sendCloseContainer(cid);
		}
	}
}

void SpyViewer::sendChannel(uint16_t channelId, const std::string &channelName, const std::map<uint32_t, std::shared_ptr<Player>>* channelUsers, const std::map<uint32_t, std::shared_ptr<Player>>* invitedUsers) {
	if (m_owner) {
		m_owner->sendChannel(channelId, channelName, channelUsers, invitedUsers);
	}
}

void SpyViewer::sendTutorial(uint8_t tutorialId) {
	if (m_owner) {
		m_owner->sendTutorial(tutorialId);
	}
}

void SpyViewer::sendAddMarker(const Position &pos, uint8_t markType, const std::string &desc) {
	if (m_owner) {
		m_owner->sendAddMarker(pos, markType, desc);
	}
}

void SpyViewer::sendFightModes() {
	if (m_owner) {
		m_owner->sendFightModes();
	}
}

void SpyViewer::writeToOutputBuffer(const NetworkMessage &message) {
	if (m_owner) {
		m_owner->writeToOutputBuffer(message);

		for (const auto &it : m_viewers) {
			it.first->writeToOutputBuffer(message);
		}
	}
}

void SpyViewer::sendAddCreature(std::shared_ptr<Creature> creature, const Position &pos, int32_t stackpos, bool isLogin) {
	if (m_owner) {
		m_owner->sendAddCreature(creature, pos, stackpos, isLogin);

		for (const auto &it : m_viewers) {
			it.first->sendAddCreature(creature, pos, stackpos, isLogin);
		}
	}
}

void SpyViewer::sendHouseWindow(uint32_t windowTextId, const std::string &text) {
	if (m_owner) {
		m_owner->sendHouseWindow(windowTextId, text);
	}
}

void SpyViewer::sendCloseTrade() const {
	if (m_owner) {
		m_owner->sendCloseTrade();
	}
}

void SpyViewer::sendBestiaryCharms() {
	if (m_owner) {
		m_owner->sendBestiaryCharms();
	}
}

void SpyViewer::sendImbuementResult(const std::string message) {
	if (m_owner) {
		m_owner->sendImbuementResult(message);
	}
}

void SpyViewer::closeImbuementWindow() {
	if (m_owner) {
		m_owner->closeImbuementWindow();
	}
}

void SpyViewer::sendPodiumWindow(std::shared_ptr<Item> podium, const Position &position, uint16_t itemId, uint8_t stackpos) {
	if (m_owner) {
		m_owner->sendPodiumWindow(podium, position, itemId, stackpos);
	}
}

void SpyViewer::sendCreatureIcon(std::shared_ptr<Creature> creature) {
	if (m_owner && !m_owner->oldProtocol) {
		m_owner->sendCreatureIcon(creature);
	}
}

void SpyViewer::sendUpdateCreature(std::shared_ptr<Creature> creature) {
	if (m_owner) {
		m_owner->sendUpdateCreature(creature);
	}
}

void SpyViewer::sendCreatureType(std::shared_ptr<Creature> creature, uint8_t creatureType) {
	if (m_owner) {
		m_owner->sendCreatureType(creature, creatureType);
	}
}

void SpyViewer::sendSpellCooldown(uint16_t spellId, uint32_t time) {
	if (m_owner) {
		m_owner->sendSpellCooldown(spellId, time);
	}
}

void SpyViewer::sendSpellGroupCooldown(SpellGroup_t groupId, uint32_t time) {
	if (m_owner) {
		m_owner->sendSpellGroupCooldown(groupId, time);
	}
}

void SpyViewer::sendUseItemCooldown(uint32_t time) {
	if (m_owner) {
		m_owner->sendUseItemCooldown(time);
	}
}

void SpyViewer::reloadCreature(std::shared_ptr<Creature> creature) {
	if (m_owner) {
		m_owner->reloadCreature(creature);
	}
}

void SpyViewer::sendBestiaryEntryChanged(uint16_t raceid) {
	if (m_owner) {
		m_owner->sendBestiaryEntryChanged(raceid);
	}
}

void SpyViewer::refreshCyclopediaMonsterTracker(const std::unordered_set<std::shared_ptr<MonsterType>> &trackerList, bool isBoss) const {
	if (m_owner) {
		m_owner->refreshCyclopediaMonsterTracker(trackerList, isBoss);
	}
}

void SpyViewer::sendClientCheck() {
	if (m_owner) {
		m_owner->sendClientCheck();
	}
}

void SpyViewer::sendGameNews() {
	if (m_owner) {
		m_owner->sendGameNews();
	}
}

void SpyViewer::removeMagicEffect(const Position &pos, uint16_t type) {
	if (m_owner) {
		m_owner->removeMagicEffect(pos, type);
	}
}

void SpyViewer::sendPingBack() {
	if (m_owner) {
		m_owner->sendPingBack();

		for (const auto &it : m_viewers) {
			it.first->sendPingBack();
		}
	}
}

void SpyViewer::sendBasicData() {
	if (m_owner) {
		m_owner->sendBasicData();
	}
}

void SpyViewer::sendBlessStatus() {
	if (m_owner) {
		m_owner->sendBlessStatus();
	}
}

void SpyViewer::updatePartyTrackerAnalyzer(const std::shared_ptr<Party> party) {
	if (m_owner && party) {
		m_owner->updatePartyTrackerAnalyzer(party);
	}
}

void SpyViewer::createLeaderTeamFinder(NetworkMessage &msg) {
	if (m_owner) {
		m_owner->createLeaderTeamFinder(msg);
	}
}

void SpyViewer::sendLeaderTeamFinder(bool reset) {
	if (m_owner) {
		m_owner->sendLeaderTeamFinder(reset);
	}
}

void SpyViewer::sendTeamFinderList() {
	if (m_owner) {
		m_owner->sendTeamFinderList();
	}
}

void SpyViewer::sendCreatureHelpers(uint32_t creatureId, uint16_t helpers) {
	if (m_owner) {
		m_owner->sendCreatureHelpers(creatureId, helpers);
	}
}

void SpyViewer::sendChannelEvent(uint16_t channelId, const std::string &playerName, ChannelEvent_t channelEvent) {
	if (m_owner) {
		m_owner->sendChannelEvent(channelId, playerName, channelEvent);
	}
}

void SpyViewer::sendDepotItems(const ItemsTierCountList &itemMap, uint16_t count) {
	if (m_owner) {
		m_owner->sendDepotItems(itemMap, count);
	}
}

void SpyViewer::sendCloseDepotSearch() {
	if (m_owner) {
		m_owner->sendCloseDepotSearch();
	}
}

using ItemVector = std::vector<std::shared_ptr<Item>>;
void SpyViewer::sendDepotSearchResultDetail(uint16_t itemId, uint8_t tier, uint32_t depotCount, const ItemVector &depotItems, uint32_t inboxCount, const ItemVector &inboxItems, uint32_t stashCount) {
	if (m_owner) {
		m_owner->sendDepotSearchResultDetail(itemId, tier, depotCount, depotItems, inboxCount, inboxItems, stashCount);
	}
}

void SpyViewer::sendCoinBalance() {
	if (m_owner) {
		m_owner->sendCoinBalance();
	}
}

void SpyViewer::sendInventoryIds() {
	if (m_owner) {
		m_owner->sendInventoryIds();
	}
}

void SpyViewer::sendLootContainers() {
	if (m_owner) {
		m_owner->sendLootContainers();
	}
}

void SpyViewer::sendSingleSoundEffect(const Position &pos, SoundEffect_t id, SourceEffect_t source) {
	if (m_owner) {
		m_owner->sendSingleSoundEffect(pos, id, source);
	}
}

void SpyViewer::sendDoubleSoundEffect(const Position &pos, SoundEffect_t mainSoundId, SourceEffect_t mainSource, SoundEffect_t secondarySoundId, SourceEffect_t secondarySource) {
	if (m_owner) {
		m_owner->sendDoubleSoundEffect(pos, mainSoundId, mainSource, secondarySoundId, secondarySource);
	}
}

void SpyViewer::sendCreatureEmblem(std::shared_ptr<Creature> creature) {
	if (m_owner) {
		m_owner->sendCreatureEmblem(creature);
	}
}

void SpyViewer::sendItemInspection(uint16_t itemId, uint8_t itemCount, std::shared_ptr<Item> item, bool cyclopedia) {
	if (m_owner) {
		m_owner->sendItemInspection(itemId, itemCount, item, cyclopedia);
	}
}

void SpyViewer::sendCyclopediaCharacterNoData(CyclopediaCharacterInfoType_t characterInfoType, uint8_t errorCode) {
	if (m_owner) {
		m_owner->sendCyclopediaCharacterNoData(characterInfoType, errorCode);
	}
}

void SpyViewer::sendCyclopediaCharacterBaseInformation() {
	if (m_owner) {
		m_owner->sendCyclopediaCharacterBaseInformation();
	}
}

void SpyViewer::sendCyclopediaCharacterGeneralStats() {
	if (m_owner) {
		m_owner->sendCyclopediaCharacterGeneralStats();
	}
}

void SpyViewer::sendCyclopediaCharacterCombatStats() {
	if (m_owner) {
		m_owner->sendCyclopediaCharacterCombatStats();
	}
}

void SpyViewer::sendCyclopediaCharacterRecentDeaths(uint16_t page, uint16_t pages, const std::vector<RecentDeathEntry> &entries) {
	if (m_owner) {
		m_owner->sendCyclopediaCharacterRecentDeaths(page, pages, entries);
	}
}

void SpyViewer::sendOpenForge() {
	if (m_owner) {
		m_owner->sendOpenForge();
	}
}

void SpyViewer::sendForgeError(ReturnValue returnValue) {
	if (m_owner) {
		m_owner->sendForgeError(returnValue);
	}
}

void SpyViewer::sendForgeHistory(uint8_t page) const {
	if (m_owner) {
		m_owner->sendForgeHistory(page);
	}
}

void SpyViewer::closeForgeWindow() const {
	if (m_owner) {
		m_owner->closeForgeWindow();
	}
}

void SpyViewer::sendBosstiaryCooldownTimer() const {
	if (m_owner) {
		m_owner->sendBosstiaryCooldownTimer();
	}
}

void SpyViewer::sendCyclopediaCharacterRecentPvPKills(uint16_t page, uint16_t pages, const std::vector<RecentPvPKillEntry> &entries) {
	if (m_owner) {
		m_owner->sendCyclopediaCharacterRecentPvPKills(page, pages, entries);
	}
}

void SpyViewer::sendCyclopediaCharacterAchievements(int16_t secretsUnlocked, std::vector<std::pair<Achievement, uint32_t>> achievementsUnlocked) {
	if (m_owner) {
		m_owner->sendCyclopediaCharacterAchievements(secretsUnlocked, achievementsUnlocked);
	}
}

void SpyViewer::sendCyclopediaCharacterItemSummary(const ItemsTierCountList &inventoryItems, const ItemsTierCountList &storeInboxItems, const StashItemList &supplyStashItems, const ItemsTierCountList &depotBoxItems, const ItemsTierCountList &inboxItems) {
	if (m_owner) {
		m_owner->sendCyclopediaCharacterItemSummary(inventoryItems, storeInboxItems, supplyStashItems, depotBoxItems, inboxItems);
	}
}

void SpyViewer::sendCyclopediaCharacterOutfitsMounts() {
	if (m_owner) {
		m_owner->sendCyclopediaCharacterOutfitsMounts();
	}
}

void SpyViewer::sendCyclopediaCharacterStoreSummary() {
	if (m_owner) {
		m_owner->sendCyclopediaCharacterStoreSummary();
	}
}

void SpyViewer::sendCyclopediaCharacterInspection() {
	if (m_owner) {
		m_owner->sendCyclopediaCharacterInspection();
	}
}

void SpyViewer::sendCyclopediaCharacterBadges() {
	if (m_owner) {
		m_owner->sendCyclopediaCharacterBadges();
	}
}

void SpyViewer::sendCyclopediaCharacterTitles() {
	if (m_owner) {
		m_owner->sendCyclopediaCharacterTitles();
	}
}

void SpyViewer::sendHighscoresNoData() {
	if (m_owner) {
		m_owner->sendHighscoresNoData();
	}
}

void SpyViewer::sendHighscores(const std::vector<HighscoreCharacter> &characters, uint8_t categoryId, uint32_t vocationId, uint16_t page, uint16_t pages, uint32_t updateTimer) {
	if (m_owner) {
		m_owner->sendHighscores(characters, categoryId, vocationId, page, pages, updateTimer);
	}
}

void SpyViewer::sendMonsterPodiumWindow(std::shared_ptr<Item> podium, const Position &position, uint16_t itemId, uint8_t stackpos) {
	if (m_owner) {
		m_owner->sendMonsterPodiumWindow(podium, position, itemId, stackpos);
	}
}

void SpyViewer::sendBosstiaryEntryChanged(uint32_t bossid) {
	if (m_owner) {
		m_owner->sendBosstiaryEntryChanged(bossid);
	}
}

void SpyViewer::sendInventoryImbuements(const std::map<Slots_t, std::shared_ptr<Item>> items) {
	if (m_owner) {
		m_owner->sendInventoryImbuements(items);

		for (const auto &it : m_viewers) {
			it.first->sendInventoryImbuements(items);
		}
	}
}

void SpyViewer::sendEnterWorld() {
	if (m_owner) {
		m_owner->sendEnterWorld();
	}
}

void SpyViewer::sendExperienceTracker(int64_t rawExp, int64_t finalExp) {
	if (m_owner) {
		m_owner->sendExperienceTracker(rawExp, finalExp);
	}
}

void SpyViewer::sendItemsPrice() {
	if (m_owner) {
		m_owner->sendItemsPrice();
	}
}

void SpyViewer::sendForgingData() {
	if (m_owner) {
		m_owner->sendForgingData();
	}
}

void SpyViewer::sendKillTrackerUpdate(std::shared_ptr<Container> corpse, const std::string &name, const Outfit_t creatureOutfit) {
	if (m_owner) {
		m_owner->sendKillTrackerUpdate(corpse, name, creatureOutfit);
	}
}

void SpyViewer::sendMarketLeave() {
	if (m_owner) {
		m_owner->sendMarketLeave();
	}
}

void SpyViewer::sendMarketBrowseItem(uint16_t itemId, const MarketOfferList &buyOffers, const MarketOfferList &sellOffers, uint8_t tier) {
	if (m_owner) {
		m_owner->sendMarketBrowseItem(itemId, buyOffers, sellOffers, tier);
	}
}

void SpyViewer::sendMarketBrowseOwnOffers(const MarketOfferList &buyOffers, const MarketOfferList &sellOffers) {
	if (m_owner) {
		m_owner->sendMarketBrowseOwnOffers(buyOffers, sellOffers);
	}
}

void SpyViewer::sendMarketBrowseOwnHistory(const HistoryMarketOfferList &buyOffers, const HistoryMarketOfferList &sellOffers) {
	if (m_owner) {
		m_owner->sendMarketBrowseOwnHistory(buyOffers, sellOffers);
	}
}

void SpyViewer::sendMarketDetail(uint16_t itemId, uint8_t tier) {
	if (m_owner) {
		m_owner->sendMarketDetail(itemId, tier);
	}
}

void SpyViewer::sendMarketAcceptOffer(const MarketOfferEx &offer) {
	if (m_owner) {
		m_owner->sendMarketAcceptOffer(offer);
	}
}

void SpyViewer::sendMarketCancelOffer(const MarketOfferEx &offer) {
	if (m_owner) {
		m_owner->sendMarketCancelOffer(offer);
	}
}

void SpyViewer::sendMessageDialog(const std::string &message) {
	if (m_owner) {
		m_owner->sendMessageDialog(message);
	}
}

void SpyViewer::sendOpenStash() {
	if (m_owner) {
		m_owner->sendOpenStash();
	}
}

void SpyViewer::sendPartyCreatureUpdate(std::shared_ptr<Creature> creature) {
	if (m_owner) {
		m_owner->sendPartyCreatureUpdate(creature);
	}
}

void SpyViewer::sendPartyCreatureShield(std::shared_ptr<Creature> creature) {
	if (m_owner) {
		m_owner->sendPartyCreatureShield(creature);
	}
}

void SpyViewer::sendPartyCreatureSkull(std::shared_ptr<Creature> creature) {
	if (m_owner) {
		m_owner->sendPartyCreatureSkull(creature);
	}
}

void SpyViewer::sendPartyCreatureHealth(std::shared_ptr<Creature> creature, uint8_t healthPercent) {
	if (m_owner) {
		m_owner->sendPartyCreatureHealth(creature, healthPercent);
	}
}

void SpyViewer::sendPartyPlayerMana(std::shared_ptr<Player> player, uint8_t manaPercent) {
	if (m_owner) {
		m_owner->sendPartyPlayerMana(player, manaPercent);
	}
}

void SpyViewer::sendPartyCreatureShowStatus(std::shared_ptr<Creature> creature, bool showStatus) {
	if (m_owner) {
		m_owner->sendPartyCreatureShowStatus(creature, showStatus);
	}
}

void SpyViewer::sendPartyPlayerVocation(std::shared_ptr<Player> player) {
	if (m_owner) {
		m_owner->sendPartyPlayerVocation(player);
	}
}

void SpyViewer::sendPlayerVocation(std::shared_ptr<Player> player) {
	if (m_owner) {
		m_owner->sendPlayerVocation(player);
	}
}

void SpyViewer::sendPreyTimeLeft(const std::unique_ptr<PreySlot> &slot) {
	if (m_owner) {
		m_owner->sendPreyTimeLeft(slot);
	}
}

void SpyViewer::sendResourcesBalance(uint64_t money, uint64_t bank, uint64_t preyCards, uint64_t taskHunting, uint64_t forgeDust, uint64_t forgeSliver, uint64_t forgeCores) {
	if (m_owner) {
		m_owner->sendResourcesBalance(money, bank, preyCards, taskHunting, forgeDust, forgeSliver, forgeCores);
	}
}

void SpyViewer::sendCreatureReload(std::shared_ptr<Creature> creature) {
	if (m_owner) {
		m_owner->reloadCreature(creature);
	}
}

void SpyViewer::sendCreatureChangeOutfit(std::shared_ptr<Creature> creature, const Outfit_t &outfit) {
	if (m_owner) {
		m_owner->sendCreatureOutfit(creature, outfit);

		for (const auto &it : m_viewers) {
			it.first->sendCreatureOutfit(creature, outfit);
		}
	}
}

void SpyViewer::sendPreyData(const std::unique_ptr<PreySlot> &slot) {
	if (m_owner) {
		m_owner->sendPreyData(slot);
	}
}

void SpyViewer::sendSpecialContainersAvailable() {
	if (m_owner) {
		m_owner->sendSpecialContainersAvailable();
	}
}

void SpyViewer::sendTaskHuntingData(const std::unique_ptr<TaskHuntingSlot> &slot) {
	if (m_owner) {
		m_owner->sendTaskHuntingData(slot);
	}
}

void SpyViewer::sendTibiaTime(int32_t time) {
	if (m_owner) {
		m_owner->sendTibiaTime(time);
	}
}

void SpyViewer::sendUpdateInputAnalyzer(CombatType_t type, int32_t amount, std::string target) {
	if (m_owner) {
		m_owner->sendUpdateInputAnalyzer(type, amount, target);
	}
}

void SpyViewer::sendRestingStatus(uint8_t protection) {
	if (m_owner) {
		m_owner->sendRestingStatus(protection);
	}
}

void SpyViewer::AddItem(NetworkMessage &msg, std::shared_ptr<Item> item) {
	if (m_owner) {
		m_owner->AddItem(msg, item);
	}
}

void SpyViewer::AddItem(NetworkMessage &msg, uint16_t id, uint8_t count, uint8_t tier) {
	if (m_owner) {
		m_owner->AddItem(msg, id, count, tier);
	}
}

void SpyViewer::parseSendBosstiary() {
	if (m_owner) {
		m_owner->parseSendBosstiary();
	}
}

void SpyViewer::parseSendBosstiarySlots() {
	if (m_owner) {
		m_owner->parseSendBosstiarySlots();
	}
}

void SpyViewer::sendLootStats(std::shared_ptr<Item> item, uint8_t count) {
	if (m_owner) {
		m_owner->sendLootStats(item, count);
	}
}

void SpyViewer::sendUpdateSupplyTracker(std::shared_ptr<Item> item) {
	if (m_owner) {
		m_owner->sendUpdateSupplyTracker(item);
	}
}

void SpyViewer::sendUpdateImpactTracker(CombatType_t type, int32_t amount) {
	if (m_owner) {
		m_owner->sendUpdateImpactTracker(type, amount);
	}
}

void SpyViewer::openImbuementWindow(std::shared_ptr<Item> item) {
	if (m_owner) {
		m_owner->openImbuementWindow(item);
	}
}

void SpyViewer::sendMarketEnter(uint32_t depotId) {
	if (m_owner) {
		m_owner->sendMarketEnter(depotId);
	}
}

void SpyViewer::sendUnjustifiedPoints(const uint8_t &dayProgress, const uint8_t &dayLeft, const uint8_t &weekProgress, const uint8_t &weekLeft, const uint8_t &monthProgress, const uint8_t &monthLeft, const uint8_t &skullDuration) {
	if (m_owner) {
		m_owner->sendUnjustifiedPoints(dayProgress, dayLeft, weekProgress, weekLeft, monthProgress, monthLeft, skullDuration);

		for (const auto &it : m_viewers) {
			it.first->sendUnjustifiedPoints(dayProgress, dayLeft, weekProgress, weekLeft, monthProgress, monthLeft, skullDuration);
		}
	}
}

void SpyViewer::sendModalWindow(const ModalWindow &modalWindow) {
	if (m_owner) {
		m_owner->sendModalWindow(modalWindow);
	}
}

void SpyViewer::sendResourceBalance(Resource_t resourceType, uint64_t value) {
	if (m_owner) {
		m_owner->sendResourceBalance(resourceType, value);
	}
}

void SpyViewer::sendOpenWheelWindow(uint32_t ownerId) {
	if (m_owner) {
		m_owner->sendOpenWheelWindow(ownerId);
	}
}

void SpyViewer::sendCreatureSay(std::shared_ptr<Creature> creature, SpeakClasses type, const std::string &text, const Position* pos) {
	if (m_owner) {
		m_owner->sendCreatureSay(creature, type, text, pos);

		if (type == TALKTYPE_PRIVATE_FROM) {
			return;
		}

		for (const auto &it : m_viewers) {
			it.first->sendCreatureSay(creature, type, text, pos);
		}
	}
}

void SpyViewer::disconnectClient(const std::string &message) const {
	if (m_owner) {
		m_owner->disconnectClient(message);
	}
}

void SpyViewer::addViewer(ProtocolGame_ptr client) {
	if (m_viewers.find(client) != m_viewers.end()) {
		return;
	}

	auto viewerId = m_viewers.size() + 1;
	std::string guestString = fmt::format("Guest-{}", viewerId);

	m_viewers[client] = std::make_pair(guestString, m_id);
}

void SpyViewer::removeViewer(ProtocolGame_ptr client) {
	auto it = m_viewers.find(client);
	if (it == m_viewers.end()) {
		return;
	}

	m_viewers.erase(it);
}

std::vector<std::string> SpyViewer::getViewers() const {
	std::vector<std::string> players;
	for (const auto &it : m_viewers) {
		players.push_back(it.second.first);
	}
	return players;
}

void SpyViewer::setSpying(bool b) {
	spying = b;
}

bool SpyViewer::isSpying() {
	return spying;
}

bool SpyViewer::isOldProtocol() {
	return oldProtocol;
}
