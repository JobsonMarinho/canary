local spy = TalkAction("/spy")

function spy.onSay(player, words, param)
	-- create log
	logCommand(player, words, param)

	if param == "" then
		player:sendCancelMessage("Write the name of the character to be spyed.")
		return true
	end

	local target = Player(param)
	if target and target:isPlayer() then
		player:spyPlayer(target)
	else
		player:sendCancelMessage("This player is offline or doesn't exist.")
	end
	return true
end

spy:separator(" ")
spy:groupType("gamemaster")
spy:register()
