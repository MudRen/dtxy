/*
created by emotion
*/

#include <mudlib.h>
inherit NPC;

string send_mail();
void create()
{
        set_name("鲁班", ({"lu ban", "lu"}));
        set("age", 42);
        set("gender", "男性");
        set("nickname", "心灵手巧");
        set("long", MUDLIB_NAME"中专门负责掌管特殊装备的大人物。\n");
	    set("title", "三界五行装备总管");
        set("attitude", "peaceful");
        set("combat_exp", 400000000000);
  		set("daoxing", 200000000);

        set("shen_type", 1);
		set("max_force", 300);
		set("force", 300);
		set("force_factor", 5);
        set_skill("unarmed", 50);
        set_skill("dodge", 60);
        set_skill("parry", 40);
        set_skill("forge", 300);
        set_skill("alchemy", 300);
        set("skill_public",1);
	setup();
        carry_object(__DIR__"obj/choupao")->wear();
}

void init() {
	object player;
	::init();
	player = this_player();
	if (!objectp(player) || !userp(player))
		return;
	add_action("do_register", "register");
	add_action("do_list", "list");
	add_action("do_fetch","fetch");
	add_action("do_deregister", "deregister");
	add_action("do_payoff", "payoff");
	add_action("do_luimprove", "luimprove");
	add_action("do_selfimprove", "selfimprove");
	add_action("do_luembed","luembed");
	add_action("do_selfembed","selfembed");
	add_action("do_upgrade", "upgrade");
}

    // 查看欠多少钱
int check_balance(object player) {
	int fee_per_day = 20;  // 20金票每天
	int days;
	int last_payoff;
	int current_time;
        int size;
	mapping items;
	last_payoff = player->query("newitem_payoff");
	if ( last_payoff <= 0 ) return 0;
	current_time = time();
	days = (current_time - last_payoff) / 3600 / 24;
	if ( days <= 0 ) return 0;
	items = player->query("newitem");
          size = sizeof(items) - 11;
	if (!mapp(items) || size <= 0 ) return 0;
	return size * fee_per_day;
}

  //付清欠款
int do_payoff() {
	int balance;
	object player, me;
	me = this_object();
	player = this_player();
	balance = check_balance(player);
	if ( balance <= 0 ) {
		message_vision("$N对$n摇了摇头, 说道: 你现在还没有欠我钱!\n", me, player);
		return 1;
	}
	if ( player->query("g_balance") < balance ) {
		message_vision("$N对$n摇了摇头, 说道: 你现钱庄没有那么多金票! 你欠我" + balance + "两金票!\n", me, player);
		return 1;
	}
	player->add("g_balance", -balance);
	player->set("newitem_payoff", time());
	player->save();
	message_vision("$N对$n点了点头, 说道: 很好，我已经派人从钱庄中搬走了" + balance + "两金票!\n", me, player);
	log_file("newitem", player->query("name") + "(" + player->query("id") + ") 支付了" + balance + "两金票的保管费\n");
	return 1;
}

// 查看自己注册过的物品
int do_list(string arg) {
	object player, me;
	mapping item_list, temp_map;
	string* key;
	string msg;
	int size, count, i;
	player = this_player();
	me = this_object();
	if (!arg || (arg != "all" && arg != "weapon" && arg != "armor" && arg != "stone")) {
		message_vision("$N对$n摇了摇头, 说道: 查询物品需要用 list all|weapon|armor|stone!\n", me, player);
		return 1;
	}
	item_list = player->query("newitem");
	if (!mapp(item_list)) {
		message_vision("$N对$n摇了摇头, 说道: 你现在没有任何物品注册在案!\n", me, player);
		return 1;
	}
	key = keys(item_list);
	size = sizeof(key);
	if ( size == 0 ) {
		message_vision("$N对$n摇了摇头, 说道: 你现在没有任何物品注册在案!\n", me, player);
		return 1;
	}
	count = 0;
	msg = "====================================\n";
	for (i = 0; i < size; i++) {
		string id, name, type, temp;
		id = key[i];
		name = player->query("newitem/" + id + "/name");
		type = player->query("newitem/" + id + "/type");
		if (arg == "all" || type == arg) {
			count++;
			msg += sprintf("%-15s\t\t%s", id, name) + "\n";
		}
	}
	if (count == 0) {
		msg = "你现在并没有任何" + arg + "类型的物品注册在案!\n";
	} else {
		msg += "====================================\n你共有" + count + "件" + arg + "类型的物品注册在案\n";
	}
	start_more(msg);
	return 1;
}

// 取装备
int do_fetch(string arg) {
	object player, me;
	object item;
	string file;
	string* ids;
	string* key;
	mapping attrs;
	int j;
	int balance;
	player = this_player();
	me = this_object();
	balance = check_balance(player);
	if ( balance > 0 ) {
		message_vision("$N对$n摇了摇头, 说道: 你还欠我" + balance
		               + "两金票的物品保管费．先付清了(payoff)才好继续找我办事!\n", me, player);
		return 1;
	}
	if (!arg) {
		message_vision("$N对$n摇了摇头, 说道: 提取物品需要用 fetch <物品id>!\n", me, player);
		return 1;
	}
	item = present(arg, player);
	if (objectp(item)) {
		message_vision("$N对$n摇了摇头, 说道: 你身上已经有相同id的物品了!\n", me, player);
		return 1;
	}
	attrs = player->query("newitem/" + arg + "/attr");
	file = player->query("newitem/" + arg + "/file");
	ids = player->query("newitem/" + arg + "/ids");
	if (!file || !mapp(attrs) || !arrayp(ids)) {
		message_vision("$N对$n摇了摇头, 说道: 你没有注册过这样物品吧!\n", me, player);
		return 1;
	}
	item = new(file);
	if (!objectp(item)) {
		message_vision("$N对$n急道: 糟了，　出故障了，快找wiz看看吧!　不过别担心，你的装备没丢!\n", me, player);
		return 1;
	}
    key=keys(attrs);
    key = sort_array(key, 0);
    for(j=0; j<sizeof(key); j++) {
       	item->set(key[j], attrs[key[j]]);
    }
    item->set_name(item->query("name"), ids);
    item->delete("equipped");
    item->set("no_put", 1);
    item->set("no_sell", 1);
    item->set("no_drop", 1);
    item->set("no_give", 1);
    item->move(player);
    message_vision("$N对$n点了点头道: 东西给你了，自己看看吧!\n", me, player);
    log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提取了"
             + item->query("name") + "(" + item->query("id") + ")\n");
	return 1;
}

  // calculate item registration cost
  // unit is gold
int register_cost(object item) {
	int max_level, cost, maximum_level;
	max_level = item->query("max_level");
	maximum_level = item->query("maximum_level");
	cost = 0;
	if ( max_level > 0 ) {
		if ( item->is_weapon() )
			cost = 50 * ( max_level*max_level );
		else if (item->is_armor())
			cost = 20 * ( max_level*max_level );
		else if (item->is_acc())
			cost = 20 * ( max_level*max_level );
	}
	else
		cost = item->query("register_cost");
	if ( cost == 0 )
		cost = 100;
	return cost;
}

  // 注册装备
int do_register(string arg) {
	object player, me;
	object item;
	string* ids;
	int cost, balance;
	player = this_player();
	me = this_object();
	balance = check_balance(player);
	if ( balance > 0 ) {
		message_vision("$N对$n摇了摇头, 说道: 你还欠我" + balance
		               + "两金票的物品保管费．先付清了(payoff)才好继续找我办事!\n", me, player);
		return 1;
	}
	if (!arg) {
		message_vision("$N对$n摇了摇头, 说道: 注册物品需要用 register <物品id>!\n", me, player);
		return 1;
	}
	item = present(arg, player);
	if (!objectp(item)) {
		message_vision("$N对$n摇了摇头, 说道: 你没有这样东西, 别在我这里胡搞, 我忙着哪!\n", me, player);
		return 1;
	}
	if (!item->is_newitem()) {
		message_vision("$N对$n摇了摇头, 说道: 只有特殊物品才可以在我这里注册!\n", me, player);
		return 1;
	}
	if (item->query("newitem_owner_id")) {
		if ( item->query("newitem_owner_id") != player->query("id") ) {
			message_vision("$N突然圆睁二目, 对$n大声骂道: NND, 竟敢用别人注册过的东西来骗钱! 东西我没收了, 你利用bug的行为已经被记录在案, 等wiz上线乱棒打死!\n", me, player);
			log_file("bug", player->query("name") + "(" + player->query("id") + ")" + "注册有主的东西 "
			         + item->query("name") + "(" + item->query("id") + ")" + "原主人(" + item->query("newitem_owner_id")
			         + ")\n");
			destruct(item);
		} else {
			message_vision("$N对$n摇了摇头, 说道: 这件物品你不是已经注册了吗? 我可没有功夫陪你玩!\n", me, player);
		}
		return 1;
	}
	if (player->query("newitem/" + item->query("id"))) {
		message_vision("$N对$n摇了摇头, 说道: 同名的物品每个人只可以注册一件．你已经有一个同名的物品注册了!\n",
		               me, player);
		return 1;
	}
	cost = register_cost(item);
	if (player->query("g_balance") < cost) {
		message_vision("$N对$n摇了摇头, 说道: 注册这个东西需要 " + cost + " 两金票．但是你在钱庄的金库中没有存放这么多!\n",
		               me, player);
		return 1;
	}
	item->set("newitem_owner_id", player->query("id"));
    item->set("no_put", 1);
    item->set("no_sell", 1);
    item->set("no_drop", 1);
    item->set("no_give", 1);
    item->set("no_get", 1);
	player->add("g_balance", -cost);
	player->set("newitem/" + item->query("id") + "/file", base_name(item));
	player->set("newitem/" + item->query("id") + "/attr", item->query_entire_dbase());
	player->set("newitem/" + item->query("id") + "/name", item->query("name"));
	if ( item->is_weapon() ) player->set("newitem/" + item->query("id") + "/type", "weapon");
	if ( item->is_armor() ) player->set("newitem/" + item->query("id") + "/type", "armor");
	if ( item->is_acc() ) player->set("newitem/" + item->query("id") + "/type", "armor");
	if ( item->is_magic_stone() ) player->set("newitem/" + item->query("id") + "/type", "stone");
	ids = item->query_my_id();
	player->set("newitem/" + item->query("id") + "/ids", ids);
	if (!player->query("newitem_payoff")) player->set("newitem_payoff", time());
	player->save();
	message_vision("$N笑眯眯地对$n说道: 这个东西我帮你注册了. 我已经派人从你在钱庄金库中存放的金粒中搬走了\n"
	               + cost + " 两金票．做为注册费!\n", me, player);
    log_file("newitem", player->query("name") + "(" + player->query("id") + ") 注册了"
             + item->query("name") + "(" + item->query("id") + ")花了" + cost + "两金票\n");
	return 1;
}

  // 注销装备
int do_deregister(string arg) {
	object player, me;
	object item;
	string* ids;
	int cost;
	mapping items;
	player = this_player();
	me = this_object();
	if (!arg) {
		message_vision("$N对$n摇了摇头, 说道: 注消物品需要用 deregister <物品id>!\n", me, player);
		return 1;
	}
	item = present(arg, player);
	if (!objectp(item)) {
		message_vision("$N对$n摇了摇头, 说道: 你身上没有这样东西怎么注销?\n", me, player);
		return 1;
	}
	if (!item->is_newitem()) {
		message_vision("$N对$n摇了摇头, 说道: 只有特殊物品才可以在我这里注销!\n", me, player);
		return 1;
	}
	if (!item->query("newitem_owner_id")) {
		message_vision("$N对$n摇了摇头, 说道: 这件物品你还没有注册过!\n", me, player);
		return 1;
	}
	if ( item->query("newitem_owner_id") != player->query("id") ) {
		message_vision("$N突然圆睁二目, 对$n大声骂道: NND, 竟敢用别人注册过的东西来骗钱! 东西我没收了, 你利用bug的行为已经被记录在案, 等wiz上线乱棒打死!\n", me, player);
		log_file("bug", player->query("name") + "(" + player->query("id") + ")" + "注销有主的东西 "
		         + item->query("name") + "(" + item->query("id") + ")" + "原主人(" + item->query("newitem_owner_id")
		         + ")\n");
		destruct(item);
		return 1;
	}
	if (!player->query("newitem/" + item->query("id"))) {
		message_vision("$N突然圆睁二目, 对$n大声骂道: NND, 竟敢用已经注销过的东西来骗钱! 东西我没收了, 你利用bug的行为已经被记录在案, 等wiz上线乱棒打死!\n", me, player);
		log_file("bug", player->query("name") + "(" + player->query("id") + ")" + "注销已经注销的的东西 "
		         + item->query("name") + "(" + item->query("id") + ")" + "物品记录主人(" + item->query("newitem_owner_id")
		         + ")\n");
		destruct(item);
		return 1;
	}
	item->delete("newitem_owner_id");
	item->delete("no_put");
	item->delete("no_sell");
	item->delete("no_drop");
	item->delete("no_give");
	item->delete("no_get");
	player->delete("newitem/" + item->query("id"));
	items = player->query("newitem");
	if (!mapp(items) || sizeof(items) == 0) {
		player->delete("newitem");
		player->delete("newitem_payoff");
	}
	player->save();
	message_vision("$N对$n点了点头, 说道: 该物品已经帮你注销了，这次我就不收你钱了!\n",
		             me, player);
    log_file("newitem", player->query("name") + "(" + player->query("id") + ") 注销了"
             + item->query("name") + "(" + item->query("id") + ")\n");
	return 1;
}

void adjust_player_skills(object player) {
	int wx,dx;
	int wx_skill, dx_skill;
	int i, size,skill_level;
	string skill_name, skill_type;
	mapping skills, skill_map;
	string* key;
	wx = player->query("combat_exp");
	dx = player->query("daoxing");
	wx_skill = to_int(pow(to_float(wx) * to_float(10), to_float(1)/to_float(3)));
	dx_skill = to_int(pow(to_float(dx) * to_float(10), to_float(1)/to_float(3)));
	skills = player->query_skills();
	if (!mapp(skills) || sizeof(skills) == 0 )
		return;
	key = keys(skills);
	size = sizeof(key);
	for (i=0;i<size;i++) {
		skill_name = key[i];
		skill_level = skills[skill_name];
		skill_type = SKILL_D(skill_name)->type();
		if( skill_type=="martial" && skill_level > wx_skill ) {
			player->set_skill(skill_name, wx_skill);
			log_file("newitem", player->query("name") + "(" + player->query("id") + ") 的"
	           + skill_name + "从" + skill_level + "降到" + wx_skill + "\n");
		}
		else if( skill_type=="magic" && skill_level > dx_skill ) {
			player->set_skill(skill_name, dx_skill);
			log_file("newitem", player->query("name") + "(" + player->query("id") + ") 的"
	           + skill_name + "从" + skill_level + "降到" + dx_skill + "\n");
		}

	}
}

int improve(object me, object player, object provider, string item_id, string attr) {
	int original_value, new_value, item_level, wx_cost, dx_cost, skill_level,gold_cost;
	string item_name;
	object item;
	if (player->is_busy()) {
		tell_object(player, "你现在正忙!\n");
		return 0;
	}
	item = present(item_id, player);
	if (!objectp(item)) {
		message_vision("$N对$n摇了摇头, 说道: 你身上没有这样东西!\n", me, player);
		return 0;
	}
	item_name = item->query("name");
	item_id = item->query("id");
	if ( !item->is_newitem() ) {
		message_vision("$N对$n摇了摇头, 说道: 特殊物品才可以在我这里增强属性!\n", me, player);
		return 0;
	}
	if (item->query("equipped")) {
		message_vision("$N对$n摇了摇头, 说道: 你先解除这个 " + item_name + " 再说吧!\n", me, player);
		return 0;
	}
	if ( !item->is_armor() && !item->is_weapon() && !item->is_magic_stone() && !item->is_acc() ) {
		message_vision("$N对$n摇了摇头, 说道: 怪了, 这件东西我从没见过, 找wiz看看吧!\n", me, player);
		return 0;
	}
	if ( item->is_weapon() ) {
		/*if ( attr != "damage" && attr != "gold_attack" && attr != "wood_attack"
		      && attr != "water_attack"  && attr != "fire_attack"  && attr != "earth_attack" ) {
			message_vision("$N对$n摇了摇头, 说道: 你只可以加这些属性 damage,gold_attack,wood_attack,water_attack,fire_attack,earth_attack!\n", me, player);
			return 0;
		}*/
		if ( attr != "damage" ) {
			message_vision("$N对$n摇了摇头, 说道: 你只可以加 damage属性!\n", me, player);
			return 0;
		}
		if ( attr == "damage" ) {
			original_value = item->query("weapon_prop/damage");
			if (original_value < 0) {
				message_vision("$N对$n摇了摇头, 说道: " + item_name + " 的damage居然是负, 怪了!\n",
				      me, player);
				return 0;
			}
			new_value = original_value + 1;
			item_level = item->query("level");
			//if (new_value > item_level * 50) {
			if (new_value > item_level * 40) {
				message_vision("$N对$n摇了摇头, 说道: 对于 " + item_name + " 目前的等级来说, 它的damage已经足够高了!\n",
				      me, player);
				return 0;
			}
			wx_cost = new_value * new_value;
			//add by kugu
			if( !item->query("maximum_level") ) item->set("maximum_level",item->query("max_level"));
			if( item->query("maximum_level") > 9 ) item->set("maximum_level",9);
			wx_cost = wx_cost * item->query("max_level") / item->query("maximum_level");
			wx_cost = wx_cost/(10-item->query("maximum_level"));
			gold_cost = new_value/(10-item->query("maximum_level"));
			if( gold_cost < 1 ) gold_cost = 1;
			//end
			if (wx_cost < 100) wx_cost = 100;
			if (random(player->query("int") + player->query("kar") + 1000 )
			    < ( player->query("int") + player->query("kar") ) ) {
				message_vision("$N突然福至心灵, 决定少吐几口血!\n", player, me);
				wx_cost = wx_cost / 2;
			}
			if ( player->query("combat_exp") - wx_cost < 100000 ) {
				message_vision("$N对$n摇了摇头, 说道: 以你这么点武学经验, 恐怕没有几口血好吐吧?\n", me, player);
				return 0;
			}
			if ( (player->query("combat_exp") - wx_cost)/1000 < item->query("wield/daoxing") ) {
				message_vision("$N对$n摇了摇头, 说道: 凭你这点经验，无法升级如此高级的武器！\n", me, player);
				return 0;
			}
			if (provider == me) {
				if (player->query("g_balance") < gold_cost) {
					message_vision("$N对$n摇了摇头, 说道: 我需要" + gold_cost + "两金票作为服务费. 你在钱庄中没有这么多!\n",
				      	me, player);
					return 0;
				}
				player->add("g_balance", -gold_cost);
				message_vision("$N对$n点了点头, 说道: 我派人从你在钱庄中的户头里拿走了" + gold_cost + "两金票作为服务费!\n",
				      me, player);
			}
			skill_level = provider->query_skill("forge",1);
			player->add("combat_exp", -wx_cost);
			adjust_player_skills(player);
			if ( random(skill_level + new_value ) >= skill_level ) {
				player->save();
				player->start_busy(1);
				if ( player != provider ) {
					message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血喷到" + item_name + "上\n"
					  + "可是$n呆了一呆, 叹道: 完蛋了, 血白吐了!\n$N损失了" + wx_cost + "点武行\n", player, provider);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                          + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性失败, 损失了"
                          + new_value + "两金票" + wx_cost + "武行\n");

				}
				else {
					message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血喷到" + item_name + "上\n"
					  + "可是$N呆了一呆, 叹道: 完蛋了, 血白吐了!\n$N损失了" + wx_cost + "点武行\n", player);
				    log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                          + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性失败, 损失了"
                          + wx_cost + "武行\n");

				}
				return 0;
			}
			item->set_item_attr("weapon_prop/damage", new_value, player);
			player->save();
			player->start_busy(1);
			if ( player != provider ) {
				message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血喷到" + item_name + "上\n"
					  + "只见" + item_name + "渐渐发出耀眼的光芒!\n$N损失了" + wx_cost + "点武行, "
					  + item_name + "的damage属性提升到" + new_value + "\n", player, provider);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                      + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性成功, 损失了"
                      + new_value + "两金票" + wx_cost + "武行\n");
			}
			else {
				message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血喷到" + item_name + "上\n"
					  + "只见" + item_name + "渐渐发出耀眼的光芒!\n$N损失了" + wx_cost + "点武行, "
					  + item_name + "的damage属性提升到" + new_value + "\n", player);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                      + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性成功, 损失了"
                      + wx_cost + "武行\n");
			}
			return 1;
		}
		/*if ( attr == "gold_attack" || attr == "wood_attack" || attr == "water_attack"
		     || attr == "fire_attack"  || attr == "earth_attack" ) {
			if (!item->query("weapon_prop/" + attr)) {
				message_vision("$N对$n摇了摇头, 说道: " + item_name + " 还没有得到对应的魔法属性!\n", me, player);
				return 0;
			}
			original_value = item->query("weapon_prop/" + attr);
			if (original_value < 0) {
				message_vision("$N对$n摇了摇头, 说道: " + item_name + " 的" + attr + "居然是负, 怪了!\n",
				      me, player);
				return 0;
			}
			new_value = original_value + 1;
			item_level = item->query("level");
			if (new_value > item_level * 40) {
				message_vision("$N对$n摇了摇头, 说道: 对于 " + item_name + " 目前的等级来说, 它的" + attr + "已经足够高了!\n",
				      me, player);
				return 0;
			}
			wx_cost = new_value * new_value;
			//add by kugu
			if( !item->query("maximum_level") ) item->set("maximum_level",item->query("max_level"));
			if( item->query("maximum_level") > 9 ) item->set("maximum_level",9);
			wx_cost = wx_cost * item->query("max_level") / item->query("maximum_level");
			wx_cost = wx_cost/(10-item->query("maximum_level"));
			gold_cost = new_value/(10-item->query("maximum_level"));
			if( gold_cost < 1 ) gold_cost = 1;
			//end
			if (wx_cost < 100) wx_cost = 100;
			dx_cost = wx_cost;
			if (random(player->query("int") + player->query("kar") + 600 )
			    < ( player->query("int") + player->query("kar") ) ) {
				message_vision("$N突然福至心灵, 决定少吐几口血和少喷几粒内丹!\n", player, me);
				wx_cost = wx_cost / 2;
				dx_cost = wx_cost;
			}
			if ( player->query("combat_exp") - wx_cost < 100000 ) {
				message_vision("$N对$n摇了摇头, 说道: 以你这么点武学经验, 恐怕没有几口血好吐吧?\n", me, player);
				return 0;
			}
			if ( player->query("daoxing") - dx_cost < 100000 ) {
				message_vision("$N对$n摇了摇头, 说道: 以你这么点道行, 恐怕肚子里面没有多少内丹?\n", me, player);
				return 0;
			}
			if (provider == me) {
				if (player->query("g_balance") < gold_cost) {
					message_vision("$N对$n摇了摇头, 说道: 我需要" + gold_cost + "两金票作为服务费. 你在钱庄中没有这么多!\n",
				      	me, player);
					return 0;
				}
				player->add("g_balance", -new_value);
				message_vision("$N对$n点了点头, 说道: 我派人从你在钱庄中的户头里拿走了" + gold_cost + "两金票作为服务费!\n",
				      me, player);
			}
			skill_level = (provider->query_skill("alchemy") + provider->query_skill("forge")) / 2;
			player->add("combat_exp", -wx_cost);
			player->add("daoxing", -dx_cost);
			adjust_player_skills(player);
			if ( random(skill_level + new_value ) >= skill_level ) {
				player->save();
				player->start_busy(1);
				if ( player != provider ) {
					message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血和几粒内丹喷到" + item_name + "上\n"
					  + "可是$n呆了一呆, 叹道: 完蛋了, 血和丹都白吐了!\n$N损失了" + wx_cost + "点武行和" + dx_cost
					  + "点道行\n", player, provider);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                          + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性失败, 损失了"
                          + new_value + "两金票" + wx_cost + "武行" + dx_cost + "道行\n");
				}
				else {
					message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血和几粒内丹喷到" + item_name + "上\n"
					  + "可是$N呆了一呆, 叹道: 完蛋了, 血和丹白吐了!\n$N损失了" + wx_cost + "点武行和" + dx_cost
					  + "点道行\n", player);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                          + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性失败, 损失了"
                          + wx_cost + "武行" + dx_cost + "道行\n");
				}
				return 0;
			}
			item->set_item_attr("weapon_prop/" + attr, new_value, player);
			player->save();
			player->start_busy(1);
			if ( player != provider ) {
				message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血和几粒内丹喷到" + item_name + "上\n"
					  + "只见" + item_name + "渐渐发出耀眼的光芒!\n$N损失了" + wx_cost + "点武行和" + dx_cost + "点道行,"
					  + item_name + "的"+attr+"属性提升到" + new_value + "\n", player, provider);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                      + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性成功, 损失了"
                      + new_value + "两金票" + wx_cost + "武行" + dx_cost + "道行\n");
			}
			else {
				message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血喷到" + item_name + "上\n"
					  + "只见" + item_name + "渐渐发出耀眼的光芒!\n$N损失了" + wx_cost + "点武行和" + dx_cost + "点道行,"
					  + item_name + "的"+attr+"属性提升到" + new_value + "\n", player);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                      + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性成功, 损失了"
                      + wx_cost + "武行" + dx_cost + "道行\n");
			}

			return 1;
		}*/
	} else if (item->is_armor() || item->is_acc()) {
		/*if ( attr != "armor" && attr != "gold_defense" && attr != "wood_defense"
		      && attr != "water_defense"  && attr != "fire_defense"  && attr != "earth_defense" ) {
			message_vision("$N对$n摇了摇头, 说道: 你只可以加这些属性 armor,gold_defense,wood_defense,water_defense,fire_defense,earth_defense!\n", me, player);
			return 0;
		}*/
		if ( attr != "armor" ) {
			message_vision("$N对$n摇了摇头, 说道: 你只可以加 armor 属性!\n", me, player);
			return 0;
		}
		if ( attr == "armor" ) {
			original_value = item->query("armor_prop/armor");
			if (original_value < 0) {
				message_vision("$N对$n摇了摇头, 说道: " + item_name + " 的armor居然是负, 怪了!\n",
				      me, player);
				return 0;
			}
			new_value = original_value + 1;
			item_level = item->query("level");
			if (new_value > item_level * 20) {
				message_vision("$N对$n摇了摇头, 说道: 对于 " + item_name + " 目前的等级来说, 它的armor已经足够高了!\n",
				      me, player);
				return 0;
			}
			wx_cost = new_value * new_value;
			//add by kugu
			if( !item->query("maximum_level") ) item->set("maximum_level",item->query("max_level"));
			if( item->query("maximum_level") > 9 ) item->set("maximum_level",9);
			wx_cost = wx_cost * item->query("max_level") / item->query("maximum_level");
			wx_cost = wx_cost/(10-item->query("maximum_level"));
			gold_cost = new_value/(10-item->query("maximum_level"));
			if( gold_cost < 1 ) gold_cost = 1;
			//end
			if (wx_cost < 100) wx_cost = 100;
			//if (wx_cost < 2000) wx_cost = 2000;
			if (random(player->query("int") + player->query("kar") + 1000 )
			    < ( player->query("int") + player->query("kar") ) ) {
				message_vision("$N突然福至心灵, 决定少吐几口血!\n", player, me);
				wx_cost = wx_cost / 2;
			}
			if ( player->query("combat_exp") - wx_cost < 100000 ) {
				message_vision("$N对$n摇了摇头, 说道: 以你这么点武学经验, 恐怕没有几口血好吐吧?\n", me, player);
				return 0;
			}
			if ( (player->query("combat_exp") - wx_cost)/1000 < item->query("wield/daoxing") ) {
				message_vision("$N对$n摇了摇头, 说道: 凭你这点经验，无法升级如此高级的防具！\n", me, player);
				return 0;
			}
			if (provider == me) {
				if (player->query("g_balance") < gold_cost) {
					message_vision("$N对$n摇了摇头, 说道: 我需要" + gold_cost + "两金票作为服务费. 你在钱庄中没有这么多!\n",
				      	me, player);
					return 0;
				}
				player->add("g_balance", -gold_cost);
				message_vision("$N对$n点了点头, 说道: 我派人从你在钱庄中的户头里拿走了" + gold_cost + "两金票作为服务费!\n",
				      me, player);
			}
			skill_level = provider->query_skill("forge",1);
			player->add("combat_exp", -wx_cost);
			adjust_player_skills(player);
			if ( random(skill_level + new_value ) >= skill_level ) {
				player->save();
				player->start_busy(1);
				if ( player != provider ) {
					message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血喷到" + item_name + "上\n"
					  + "可是$n呆了一呆, 叹道: 完蛋了, 血白吐了!\n$N损失了" + wx_cost + "点武行\n", player, provider);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                          + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性失败, 损失了"
                          + new_value + "两金票" + wx_cost + "武行\n");
				}
				else {
					message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血喷到" + item_name + "上\n"
					  + "可是$N呆了一呆, 叹道: 完蛋了, 血白吐了!\n$N损失了" + wx_cost + "点武行\n", player);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                          + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性失败, 损失了"
                          + wx_cost + "武行\n");
				}
				return 0;
			}
			item->set_item_attr("armor_prop/armor", new_value, player);
			player->save();
			player->start_busy(1);
			if ( player != provider ) {
				message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血喷到" + item_name + "上\n"
					  + "只见" + item_name + "渐渐发出耀眼的光芒!\n$N损失了" + wx_cost + "点武行, "
					  + item_name + "的armor属性提升到" + new_value + "\n", player, provider);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                      + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性成功, 损失了"
                      + new_value + "两金票" + wx_cost + "武行\n");
			}
			else {
				message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血喷到" + item_name + "上\n"
					  + "只见" + item_name + "渐渐发出耀眼的光芒!\n$N损失了" + wx_cost + "点武行, "
					  + item_name + "的armor属性提升到" + new_value + "\n", player);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                      + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性成功, 损失了"
                      + wx_cost + "武行\n");
			}
			return 1;
		}
		/*if ( attr == "gold_defense" || attr == "wood_defense" || attr == "water_defense"
		     || attr == "fire_defense"  || attr == "earth_defense" ) {
			if (!item->query("armor_prop/" + attr)) {
				message_vision("$N对$n摇了摇头, 说道: " + item_name + " 还没有镶嵌对应的魔法宝石!\n", me, player);
				return 0;
			}
			original_value = item->query("armor_prop/" + attr);
			if (original_value < 0) {
				message_vision("$N对$n摇了摇头, 说道: " + item_name + " 的" + attr + "居然是负, 怪了!\n",
				      me, player);
				return 0;
			}
			new_value = original_value + 1;
			item_level = item->query("level");
			if (new_value > item_level * 20) {
				message_vision("$N对$n摇了摇头, 说道: 对于 " + item_name + " 目前的等级来说, 它的" + attr + "已经足够高了!\n",
				      me, player);
				return 0;
			}
			wx_cost = new_value * new_value;
			//add by kugu
			if( !item->query("maximum_level") ) item->set("maximum_level",item->query("max_level"));
			if( item->query("maximum_level") > 9 ) item->set("maximum_level",9);
			wx_cost = wx_cost * item->query("max_level") / item->query("maximum_level");
			wx_cost = wx_cost/(10-item->query("maximum_level"));
			gold_cost = new_value/(10-item->query("maximum_level"));
			if( gold_cost < 1 ) gold_cost = 1;
			//end
			if (wx_cost < 100) wx_cost = 100;
			//if (wx_cost < 2000) wx_cost = 2000;
			dx_cost = wx_cost;
			if (random(player->query("int") + player->query("kar") + 600 )
			    < ( player->query("int") + player->query("kar") ) ) {
				message_vision("$N突然福至心灵, 决定少吐几口血和少喷几粒内丹!\n", player, me);
				wx_cost = wx_cost / 2;
				dx_cost = wx_cost;
			}
			if ( player->query("combat_exp") - wx_cost < 100000 ) {
				message_vision("$N对$n摇了摇头, 说道: 以你这么点武学经验, 恐怕没有几口血好吐吧?\n", me, player);
				return 0;
			}
			if ( player->query("daoxing") - dx_cost < 100000 ) {
				message_vision("$N对$n摇了摇头, 说道: 以你这么点道行, 恐怕肚子里面没有多少内丹?\n", me, player);
				return 0;
			}
			if (provider == me) {
				if (player->query("g_balance") < gold_cost) {
					message_vision("$N对$n摇了摇头, 说道: 我需要" + gold_cost + "两金票作为服务费. 你在钱庄中没有这么多!\n",
				      	me, player);
					return 0;
				}
				player->add("g_balance", -gold_cost);
				message_vision("$N对$n点了点头, 说道: 我派人从你在钱庄中的户头里拿走了" + gold_cost + "两金票作为服务费!\n",
				      me, player);
			}
			skill_level = (provider->query_skill("alchemy") + provider->query_skill("forge")) / 2;
			player->add("combat_exp", -wx_cost);
			player->add("daoxing", -dx_cost);
			adjust_player_skills(player);
			if ( random(skill_level + new_value ) >= skill_level ) {
				player->save();
				player->start_busy(1);
				if ( player != provider ) {
					message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血和几粒内丹喷到" + item_name + "上\n"
					  + "可是$n呆了一呆, 叹道: 完蛋了, 血和丹都白吐了!\n$N损失了" + wx_cost + "点武行和" + dx_cost
					  + "点道行\n", player, provider);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                          + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性失败, 损失了"
                          + new_value + "两金票" + wx_cost + "武行" + dx_cost + "道行\n");
				}
				else {
					message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血和几粒内丹喷到" + item_name + "上\n"
					  + "可是$N呆了一呆, 叹道: 完蛋了, 血和丹白吐了!\n$N损失了" + wx_cost + "点武行和" + dx_cost
					  + "点道行\n", player);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                          + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性失败, 损失了"
                          + wx_cost + "武行" + dx_cost + "道行\n");
				}
				return 0;
			}
			item->set_item_attr("armor_prop/" + attr, new_value, player);
			player->save();
			player->start_busy(1);
			if ( player != provider ) {
				message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血和几粒内丹喷到" + item_name + "上\n"
					  + "只见" + item_name + "渐渐发出耀眼的光芒!\n$N损失了" + wx_cost + "点武行和" + dx_cost + "点道行,"
					  + item_name + "的"+attr+"属性提升到" + new_value + "\n", player, provider);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                      + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性成功, 损失了"
                      + new_value + "两金票" + wx_cost + "武行" + dx_cost + "道行\n");
			}
			else {
				message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血和几粒内丹喷到" + item_name + "上\n"
					  + "只见" + item_name + "渐渐发出耀眼的光芒!\n$N损失了" + wx_cost + "点武行和" + dx_cost + "点道行,"
					  + item_name + "的"+attr+"属性提升到" + new_value + "\n", player);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                      + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性成功, 损失了"
                      + wx_cost + "武行" + dx_cost + "道行\n");
			}
			return 1;
		}*/
	} else {
		if ( attr != "gold" && attr != "wood" && attr != "water"  && attr != "fire"  && attr != "earth" ) {
			message_vision("$N对$n摇了摇头, 说道: 你只可以加这些属性 gold,wood,water,fire,earth!\n", me, player);
			return 0;
		}
		if ( attr == "gold" || attr == "wood" || attr == "water"
		     || attr == "fire"  || attr == "earth" ) {
			if (!item->query("effect/" + attr)) {
				message_vision("$N对$n摇了摇头, 说道: " + item_name + " 没有对应的魔法能力!\n", me, player);
				return 0;
			}
			original_value = item->query("effect/" + attr);
			if (original_value < 0) {
				message_vision("$N对$n摇了摇头, 说道: " + item_name + " 的" + attr + "居然是负, 怪了!\n",
				      me, player);
				return 0;
			}
			new_value = original_value + 1;
			if (new_value > 100 ) {
				message_vision("$N对$n摇了摇头, 说道: " + item_name + " 的" + attr + "已经升级满了!\n",
				      me, player);
				return 0;
			}
			dx_cost = new_value * new_value;
			//if ( item->is_super_stone() )
			//	dx_cost = dx_cost / 2;
			if (dx_cost < 100) dx_cost = 100;
			if ( random(player->query("int") + player->query("kar") + 1000)
			    < ( player->query("int") + player->query("kar") ) ) {
				message_vision("$N突然福至心灵, 决定少喷几粒内丹!\n", player, me);
				dx_cost = dx_cost / 2;
			}

			if ( player->query("daoxing") - dx_cost < 100000 ) {
				message_vision("$N对$n摇了摇头, 说道: 以你这么点道行, 恐怕肚子里面没有多少内丹?\n", me, player);
				return 0;
			}
			if (provider == me) {
				if (player->query("g_balance") < new_value) {
					message_vision("$N对$n摇了摇头, 说道: 我需要" + new_value + "两金票作为服务费. 你在钱庄中没有这么多!\n",
				      	me, player);
					return 0;
				}
				player->add("g_balance", -new_value);
				message_vision("$N对$n点了点头, 说道: 我派人从你在钱庄中的户头里拿走了" + new_value + "两金票作为服务费!\n",
				      me, player);
			}
			skill_level = provider->query_skill("alchemy",1);
			player->add("daoxing", -dx_cost);
			adjust_player_skills(player);
			if ( random(skill_level + new_value ) >= skill_level ) {
				player->save();
				player->start_busy(1);
				if ( player != provider ) {
					message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几粒内丹喷到" + item_name + "上\n"
					  + "可是$n呆了一呆, 叹道: 完蛋了, 丹白吐了!\n$N损失了" + dx_cost
					  + "点道行\n", player, provider);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                          + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性失败, 损失了"
                          + new_value + "两金票" + dx_cost + "道行\n");
				}
				else {
					message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几粒内丹喷到" + item_name + "上\n"
					  + "可是$N呆了一呆, 叹道: 完蛋了, 丹白吐了!\n$N损失了" + dx_cost
					  + "点道行\n", player);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                          + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性失败, 损失了"
                          + dx_cost + "道行\n");
				}

				return 0;
			}
			item->set_item_attr("effect/" + attr, new_value, player);
			player->save();
			player->start_busy(1);
			if ( player != provider ) {
				message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几粒内丹喷到" + item_name + "上\n"
					  + "只见" + item_name + "渐渐发出耀眼的光芒!\n$N损失了" + dx_cost + "点道行,"
					  + item_name + "的"+attr+"属性提升到" + new_value + "\n", player, provider);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                      + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性成功, 损失了"
                      + new_value + "两金票" + dx_cost + "道行\n");
			}
			else {
				message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几粒内丹喷到" + item_name + "上\n"
					  + "只见" + item_name + "渐渐发出耀眼的光芒!\n$N损失了" + dx_cost + "点道行,"
					  + item_name + "的"+attr+"属性提升到" + new_value + "\n", player);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") 提升"
                      + item->query("name") + "(" + item->query("id") + ")的" + attr + "属性成功, 损失了"
                      + dx_cost + "道行\n");
			}
			return 1;
		}
	}
}
  // 增强属性
int do_luimprove(string arg) {
	string item_id, attr;
	object player, me;
	player = this_player();
	me = this_object();
	if (!arg || sscanf(arg, "%s on %s", item_id, attr) != 2) {
		message_vision("$N对$n摇了摇头, 说道: 找我提升物品属性需要用 luimprove <物品id> on <属性>!\n", me, player);
		return 1;
	}
	improve(me, player, me, item_id, attr);
	return 1;
}

  // 增强属性
int do_selfimprove(string arg) {
	string item_id, attr;
	object player, me;
	player = this_player();
	me = this_object();
	if (!arg || sscanf(arg, "%s on %s", item_id, attr) != 2) {
		message_vision("$N对$n摇了摇头, 说道: 你自己提升物品属性需要用 selfimprove <物品id> on <属性>!\n", me, player);
		return 1;
	}
	improve(me, player, player, item_id, attr);
	return 1;
}

int embed(object me, object player, object provider, string item_id, string stone_id) {
	object item, stone;
	string item_name, stone_name, temp_str;
	int item_level, cost, wx_cost, skill_level, temp_value1, temp_value2;
	if (player->is_busy()) {
		tell_object(player, "你现在正忙!\n");
		return 0;
	}
	item = present(item_id, player);
	if (!objectp(item)) {
		message_vision("$N对$n摇了摇头, 说道: 你身上没有这样东西!\n", me, player);
		return 0;
	}
	item_name = item->query("name");
	item_id = item->query("id");
	if ( !item->is_newitem() ) {
		message_vision("$N对$n摇了摇头, 说道: 只有特殊装备才可以在我这里镶嵌宝石!\n", me, player);
		return 0;
	}
	if (item->query("equipped")) {
		message_vision("$N对$n摇了摇头, 说道: 你先解除这个 " + item_name + " 再说吧!\n", me, player);
		return 0;
	}
	if ( !item->is_armor() && !item->is_acc() && !item->is_weapon()) {
		message_vision("$N对$n摇了摇头, 说道: " + item_name + " 并不是一件武器或防具!\n", me, player);
		return 0;
	}
	if ( item->query("sockets/now") >= item->query("sockets/max")) {
		message_vision("$N对$n摇了摇头, 说道: " + item_name + " 上已经镶满宝石了!\n", me, player);
		return 0;
	}
	stone = present(stone_id, player);
	if (!objectp(stone)) {
		message_vision("$N对$n摇了摇头, 说道: 你身上没有这样东西!\n", me, player);
		return 0;
	}
	stone_name = stone->query("name");
	stone_id = stone->query("id");
	if ( !stone->is_newitem() ) {
		message_vision("$N对$n摇了摇头, 说道: 只有特殊物品才可以被用来镶嵌!\n", me, player);
		return 0;
	}
	if (stone->query("equipped")) {
		message_vision("$N对$n摇了摇头, 说道: 你先解除这个 " + item_name + " 再说吧!\n", me, player);
		return 0;
	}
	if ( !stone->is_magic_stone()) {
		message_vision("$N对$n摇了摇头, 说道: " + item_name + " 并不是一件宝石!\n", me, player);
		return 0;
	}
	item_level = item->query("max_level");
	if ( item->is_armor() || item->is_acc())
		item_level = item_level / 2;
	if ( item_level < 1 )
		item_level = 1;
	cost = item_level * item_level * 50;
	wx_cost = item_level * item_level * 1000;
	if ( player->query("combat_exp") - wx_cost < 100000 ) {
		message_vision("$N对$n摇了摇头, 说道: 以你这么点武学经验, 恐怕没有几口血好吐吧?\n", me, player);
		return 0;
	}
	if (provider == me) {
		if (player->query("g_balance") < cost) {
			message_vision("$N对$n摇了摇头, 说道: 我需要" + cost + "两金票作为服务费. 你在钱庄中没有这么多!\n",
			    	me, player);
			return 0;
		}
		player->add("g_balance", -cost);
		message_vision("$N对$n点了点头, 说道: 我派人从你在钱庄中的户头里拿走了" + cost + "两金票作为服务费!\n",
			me, player);
	}
	skill_level = provider->query_skill("forge",1);
	player->add("combat_exp", -wx_cost);
	adjust_player_skills(player);
	if ( random(skill_level + item_level * 50) >= skill_level ) {
		player->save();
		player->start_busy(1);
		if ( player != provider ) {
			message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血喷到" + item_name + "和"
			  + stone_name + "上\n"
			  + "可是$n呆了一呆, 叹道: 完蛋了, 血白吐了!\n$N损失了" + wx_cost + "点武行\n", player, provider);
			log_file("newitem", player->query("name") + "(" + player->query("id") + ") 将"
		              + stone->query("name") + "(" + stone->query("id") + ")镶嵌到"
	                  + item->query("name") + "(" + item->query("id") + ")上失败了, 损失了"
                      + cost + "两金票" + wx_cost + "武行\n");
		}
		else {
			message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血喷到" + item_name + "和"
			  + stone_name + "上\n"
			  + "可是$N呆了一呆, 叹道: 完蛋了, 血白吐了!\n$N损失了" + wx_cost + "点武行\n", player);
			log_file("newitem", player->query("name") + "(" + player->query("id") + ") 将"
		              + stone->query("name") + "(" + stone->query("id") + ")镶嵌到"
	                  + item->query("name") + "(" + item->query("id") + ")上失败了, 损失了"
                      + wx_cost + "武行\n");
		}
		return 0;
	}
	temp_value1 = stone->query("effect/gold");
	if (item->is_weapon())
		temp_str = "weapon_prop/gold_attack";
	else
		temp_str = "armor_prop/gold_defense";
	temp_value2 = item->query(temp_str);
	item->set_item_attr(temp_str, temp_value1 + temp_value2, player);
	temp_value1 = stone->query("effect/wood");
	if (item->is_weapon())
		temp_str = "weapon_prop/wood_attack";
	else
		temp_str = "armor_prop/wood_defense";
	temp_value2 = item->query(temp_str);
	item->set_item_attr(temp_str, temp_value1 + temp_value2, player);
	temp_value1 = stone->query("effect/water");
	if (item->is_weapon())
		temp_str = "weapon_prop/water_attack";
	else
		temp_str = "armor_prop/water_defense";
	temp_value2 = item->query(temp_str);
	item->set_item_attr(temp_str, temp_value1 + temp_value2, player);
	temp_value1 = stone->query("effect/fire");
	if (item->is_weapon())
		temp_str = "weapon_prop/fire_attack";
	else
		temp_str = "armor_prop/fire_defense";
	temp_value2 = item->query(temp_str);
	item->set_item_attr(temp_str, temp_value1 + temp_value2, player);
	temp_value1 = stone->query("effect/earth");
	if (item->is_weapon())
		temp_str = "weapon_prop/earth_attack";
	else
		temp_str = "armor_prop/earth_defense";
	temp_value2 = item->query(temp_str);
	item->set_item_attr(temp_str, temp_value1 + temp_value2, player);
	temp_str = item->query("embed_msg");
	if (!temp_str)
		temp_str = "";
	item->set_item_attr("embed_msg", temp_str + "<" + stone->query("name") + ">", player );
	temp_value1 = item->query("sockets/now");
	item->set_item_attr("sockets/now", temp_value1 + 1, player );
	if (stone->query("newitem_owner_id") == player->query("id"))
		player->delete("newitem/" + stone->query("id"));
	player->save();
	player->start_busy(1);
	if ( player != provider ) {
		message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血喷到" + item_name + "和"
			  + stone_name + "上\n"
		  + "只见" + item_name + "渐渐发出耀眼的光芒, 将" + stone_name+ "包容在了一起!\n$N损失了"
		  + wx_cost + "点武行\n", player, provider);
		log_file("newitem", player->query("name") + "(" + player->query("id") + ") 将"
		          + stone->query("name") + "(" + stone->query("id") + ")镶嵌到"
	              + item->query("name") + "(" + item->query("id") + ")上成功了, 损失了"
                  + cost + "两金票" + wx_cost + "武行\n");
	}
	else {
		message_vision("$N深深吸了几口气, 突然脸涨得通红, 哇哇哇地连着将几口鲜血喷到" + item_name + "和"
			  + stone_name + "上\n"
		  + "只见" + item_name + "渐渐发出耀眼的光芒, 将" + stone_name+ "包容在了一起!\n$N损失了"
		  + wx_cost + "点武行\n", player);
		log_file("newitem", player->query("name") + "(" + player->query("id") + ") 将"
		          + stone->query("name") + "(" + stone->query("id") + ")镶嵌到"
	              + item->query("name") + "(" + item->query("id") + ")上成功了, 损失了"
                  + wx_cost + "武行\n");
	}
	destruct(stone);
	return 1;
}

  // 嵌入宝石
int do_luembed(string arg) {
	string item_id, stone_id;
	object player, me;
	player = this_player();
	me = this_object();
	if (!arg || sscanf(arg, "%s in %s", stone_id, item_id) != 2) {
		message_vision("$N对$n摇了摇头, 说道: 找我镶嵌宝石需要用 luembed <宝石id> in <物品id>!\n", me, player);
		return 1;
	}
	embed(me, player, me, item_id, stone_id);
	return 1;
}

  // 嵌入宝石
int do_selfembed(string arg) {
	string item_id, stone_id;
	object player, me;
	player = this_player();
	me = this_object();
	if (!arg || sscanf(arg, "%s in %s", stone_id, item_id) != 2) {
		message_vision("$N对$n摇了摇头, 说道: 你自己镶嵌宝石需要用 selfembed <宝石id> in <物品id>!\n", me, player);
		return 1;
	}
	embed(me, player, player, item_id, stone_id);
	return 1;
}

  // 升级
int do_upgrade(string arg) {
	int cost, current_level, max_level,next_level;
	string item_name;
	object player, me, item;
	player = this_player();
	me = this_object();
	if (!arg ) {
		message_vision("$N对$n摇了摇头, 说道: 物品需要用 upgrade <物品id>!\n", me, player);
		return 1;
	}
	if (player->is_busy()) {
		tell_object(player, "你现在正忙!\n");
		return 1;
	}
	item = present(arg, player);
	if (!objectp(item)) {
		message_vision("$N对$n摇了摇头, 说道: 你身上没有这样东西!\n", me, player);
		return 1;
	}
	item_name = item->query("name");
	if ( !item->is_newitem() ) {
		message_vision("$N对$n摇了摇头, 说道: 只有特殊装备才可以在我这里升级!\n", me, player);
		return 1;
	}
	if (item->query("equipped")) {
		message_vision("$N对$n摇了摇头, 说道: 你先解除这个 " + item_name + " 再说吧!\n", me, player);
		return 1;
	}
	if ( !item->is_armor() && !item->is_acc() && !item->is_weapon()) {
		message_vision("$N对$n摇了摇头, 说道: " + item_name + " 并不是一件武器或防具!\n", me, player);
		return 1;
	}
	current_level = item->query("level");
	next_level = current_level + 1;
	max_level = item->query("max_level");
	if (current_level >= max_level) {
		message_vision("$N对$n摇了摇头, 说道: " + item_name + " 已经没有再升级的潜力了!\n", me, player);
		return 1;
	}
	if (item->fight_exp_rate() < 100) {
		message_vision("$N对$n摇了摇头, 说道: " + item_name + " 没有积累足够的战斗经验!\n", me, player);
		return 1;
	}
	//if (item->is_armor())
	//	max_level = max_level / 2;
	cost = next_level*next_level*100;
	if (item->is_armor() || item->is_acc())
		cost = cost / 2;
	if (player->query("g_balance") < cost) {
		message_vision("$N对$n摇了摇头, 说道: 我需要" + cost + "两金票作为服务费. 你在钱庄中没有这么多!\n",
		    	me, player);
		return 1;
	}
	if ( player->query("combat_exp") - cost < 100000 ) {
		message_vision("$N对$n摇了摇头, 说道: 以你这么点武学经验, 不够升级装备消耗的！\n", me, player);
		return 0;
	}
	if ( player->query("daoxing") - cost < 100000 ) {
		message_vision("$N对$n摇了摇头, 说道: 以你这么点道行, 恐怕不够升级装备消耗的！\n", me, player);
		return 0;
	}
	player->add("g_balance", -cost);
	player->add("combat_exp", -cost);
	player->add("daoxing", -cost);
	adjust_player_skills(player);
	message_vision("$N对$n点了点头, 说道: 我派人从你在钱庄中的户头里拿走了" + cost + "两金票作为服务费!\n",
		me, player);
	item->set_item_attr("level", current_level + 1, player );
	item->set_item_attr("fight_exp", 0, player );
	item->set_item_attr("op_exp", 0, player );
	player->save();
	message_vision("$N满面春风地对$n说道: " + item_name + "已经被我升级了!\n",
		me, player);
	log_file("newitem", player->query("name") + "(" + player->query("id") + ") 将"
	           + item->query("name") + "(" + item->query("id") + ")上升级到" + item->query("level") + "级, 损失了"
               + cost + "两金票\n");
	player->start_busy(1);
	return 1;
}
