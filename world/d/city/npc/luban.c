/*
created by emotion
*/

#include <mudlib.h>
inherit NPC;

string send_mail();
void create()
{
        set_name("³��", ({"lu ban", "lu"}));
        set("age", 42);
        set("gender", "����");
        set("nickname", "��������");
        set("long", MUDLIB_NAME"��ר�Ÿ����ƹ�����װ���Ĵ����\n");
	    set("title", "��������װ���ܹ�");
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

    // �鿴Ƿ����Ǯ
int check_balance(object player) {
	int fee_per_day = 20;  // 20��Ʊÿ��
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

  //����Ƿ��
int do_payoff() {
	int balance;
	object player, me;
	me = this_object();
	player = this_player();
	balance = check_balance(player);
	if ( balance <= 0 ) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: �����ڻ�û��Ƿ��Ǯ!\n", me, player);
		return 1;
	}
	if ( player->query("g_balance") < balance ) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ����Ǯׯû����ô���Ʊ! ��Ƿ��" + balance + "����Ʊ!\n", me, player);
		return 1;
	}
	player->add("g_balance", -balance);
	player->set("newitem_payoff", time());
	player->save();
	message_vision("$N��$n���˵�ͷ, ˵��: �ܺã����Ѿ����˴�Ǯׯ�а�����" + balance + "����Ʊ!\n", me, player);
	log_file("newitem", player->query("name") + "(" + player->query("id") + ") ֧����" + balance + "����Ʊ�ı��ܷ�\n");
	return 1;
}

// �鿴�Լ�ע�������Ʒ
int do_list(string arg) {
	object player, me;
	mapping item_list, temp_map;
	string* key;
	string msg;
	int size, count, i;
	player = this_player();
	me = this_object();
	if (!arg || (arg != "all" && arg != "weapon" && arg != "armor" && arg != "stone")) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ��ѯ��Ʒ��Ҫ�� list all|weapon|armor|stone!\n", me, player);
		return 1;
	}
	item_list = player->query("newitem");
	if (!mapp(item_list)) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ������û���κ���Ʒע���ڰ�!\n", me, player);
		return 1;
	}
	key = keys(item_list);
	size = sizeof(key);
	if ( size == 0 ) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ������û���κ���Ʒע���ڰ�!\n", me, player);
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
		msg = "�����ڲ�û���κ�" + arg + "���͵���Ʒע���ڰ�!\n";
	} else {
		msg += "====================================\n�㹲��" + count + "��" + arg + "���͵���Ʒע���ڰ�\n";
	}
	start_more(msg);
	return 1;
}

// ȡװ��
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
		message_vision("$N��$nҡ��ҡͷ, ˵��: �㻹Ƿ��" + balance
		               + "����Ʊ����Ʒ���ܷѣ��ȸ�����(payoff)�źü������Ұ���!\n", me, player);
		return 1;
	}
	if (!arg) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ��ȡ��Ʒ��Ҫ�� fetch <��Ʒid>!\n", me, player);
		return 1;
	}
	item = present(arg, player);
	if (objectp(item)) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: �������Ѿ�����ͬid����Ʒ��!\n", me, player);
		return 1;
	}
	attrs = player->query("newitem/" + arg + "/attr");
	file = player->query("newitem/" + arg + "/file");
	ids = player->query("newitem/" + arg + "/ids");
	if (!file || !mapp(attrs) || !arrayp(ids)) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ��û��ע���������Ʒ��!\n", me, player);
		return 1;
	}
	item = new(file);
	if (!objectp(item)) {
		message_vision("$N��$n����: ���ˣ����������ˣ�����wiz������!���������ģ����װ��û��!\n", me, player);
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
    message_vision("$N��$n���˵�ͷ��: ���������ˣ��Լ�������!\n", me, player);
    log_file("newitem", player->query("name") + "(" + player->query("id") + ") ��ȡ��"
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

  // ע��װ��
int do_register(string arg) {
	object player, me;
	object item;
	string* ids;
	int cost, balance;
	player = this_player();
	me = this_object();
	balance = check_balance(player);
	if ( balance > 0 ) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: �㻹Ƿ��" + balance
		               + "����Ʊ����Ʒ���ܷѣ��ȸ�����(payoff)�źü������Ұ���!\n", me, player);
		return 1;
	}
	if (!arg) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ע����Ʒ��Ҫ�� register <��Ʒid>!\n", me, player);
		return 1;
	}
	item = present(arg, player);
	if (!objectp(item)) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ��û����������, �������������, ��æ����!\n", me, player);
		return 1;
	}
	if (!item->is_newitem()) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ֻ��������Ʒ�ſ�����������ע��!\n", me, player);
		return 1;
	}
	if (item->query("newitem_owner_id")) {
		if ( item->query("newitem_owner_id") != player->query("id") ) {
			message_vision("$NͻȻԲ����Ŀ, ��$n�������: NND, �����ñ���ע����Ķ�����ƭǮ! ������û����, ������bug����Ϊ�Ѿ�����¼�ڰ�, ��wiz�����Ұ�����!\n", me, player);
			log_file("bug", player->query("name") + "(" + player->query("id") + ")" + "ע�������Ķ��� "
			         + item->query("name") + "(" + item->query("id") + ")" + "ԭ����(" + item->query("newitem_owner_id")
			         + ")\n");
			destruct(item);
		} else {
			message_vision("$N��$nҡ��ҡͷ, ˵��: �����Ʒ�㲻���Ѿ�ע������? �ҿ�û�й���������!\n", me, player);
		}
		return 1;
	}
	if (player->query("newitem/" + item->query("id"))) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ͬ������Ʒÿ����ֻ����ע��һ�������Ѿ���һ��ͬ������Ʒע����!\n",
		               me, player);
		return 1;
	}
	cost = register_cost(item);
	if (player->query("g_balance") < cost) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ע�����������Ҫ " + cost + " ����Ʊ����������Ǯׯ�Ľ����û�д����ô��!\n",
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
	message_vision("$NЦ���еض�$n˵��: ��������Ұ���ע����. ���Ѿ����˴�����Ǯׯ����д�ŵĽ����а�����\n"
	               + cost + " ����Ʊ����Ϊע���!\n", me, player);
    log_file("newitem", player->query("name") + "(" + player->query("id") + ") ע����"
             + item->query("name") + "(" + item->query("id") + ")����" + cost + "����Ʊ\n");
	return 1;
}

  // ע��װ��
int do_deregister(string arg) {
	object player, me;
	object item;
	string* ids;
	int cost;
	mapping items;
	player = this_player();
	me = this_object();
	if (!arg) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ע����Ʒ��Ҫ�� deregister <��Ʒid>!\n", me, player);
		return 1;
	}
	item = present(arg, player);
	if (!objectp(item)) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ������û������������ôע��?\n", me, player);
		return 1;
	}
	if (!item->is_newitem()) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ֻ��������Ʒ�ſ�����������ע��!\n", me, player);
		return 1;
	}
	if (!item->query("newitem_owner_id")) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: �����Ʒ�㻹û��ע���!\n", me, player);
		return 1;
	}
	if ( item->query("newitem_owner_id") != player->query("id") ) {
		message_vision("$NͻȻԲ����Ŀ, ��$n�������: NND, �����ñ���ע����Ķ�����ƭǮ! ������û����, ������bug����Ϊ�Ѿ�����¼�ڰ�, ��wiz�����Ұ�����!\n", me, player);
		log_file("bug", player->query("name") + "(" + player->query("id") + ")" + "ע�������Ķ��� "
		         + item->query("name") + "(" + item->query("id") + ")" + "ԭ����(" + item->query("newitem_owner_id")
		         + ")\n");
		destruct(item);
		return 1;
	}
	if (!player->query("newitem/" + item->query("id"))) {
		message_vision("$NͻȻԲ����Ŀ, ��$n�������: NND, �������Ѿ�ע�����Ķ�����ƭǮ! ������û����, ������bug����Ϊ�Ѿ�����¼�ڰ�, ��wiz�����Ұ�����!\n", me, player);
		log_file("bug", player->query("name") + "(" + player->query("id") + ")" + "ע���Ѿ�ע���ĵĶ��� "
		         + item->query("name") + "(" + item->query("id") + ")" + "��Ʒ��¼����(" + item->query("newitem_owner_id")
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
	message_vision("$N��$n���˵�ͷ, ˵��: ����Ʒ�Ѿ�����ע���ˣ�����ҾͲ�����Ǯ��!\n",
		             me, player);
    log_file("newitem", player->query("name") + "(" + player->query("id") + ") ע����"
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
			log_file("newitem", player->query("name") + "(" + player->query("id") + ") ��"
	           + skill_name + "��" + skill_level + "����" + wx_skill + "\n");
		}
		else if( skill_type=="magic" && skill_level > dx_skill ) {
			player->set_skill(skill_name, dx_skill);
			log_file("newitem", player->query("name") + "(" + player->query("id") + ") ��"
	           + skill_name + "��" + skill_level + "����" + dx_skill + "\n");
		}

	}
}

int improve(object me, object player, object provider, string item_id, string attr) {
	int original_value, new_value, item_level, wx_cost, dx_cost, skill_level,gold_cost;
	string item_name;
	object item;
	if (player->is_busy()) {
		tell_object(player, "��������æ!\n");
		return 0;
	}
	item = present(item_id, player);
	if (!objectp(item)) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ������û����������!\n", me, player);
		return 0;
	}
	item_name = item->query("name");
	item_id = item->query("id");
	if ( !item->is_newitem() ) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ������Ʒ�ſ�������������ǿ����!\n", me, player);
		return 0;
	}
	if (item->query("equipped")) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ���Ƚ����� " + item_name + " ��˵��!\n", me, player);
		return 0;
	}
	if ( !item->is_armor() && !item->is_weapon() && !item->is_magic_stone() && !item->is_acc() ) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ����, ��������Ҵ�û����, ��wiz������!\n", me, player);
		return 0;
	}
	if ( item->is_weapon() ) {
		/*if ( attr != "damage" && attr != "gold_attack" && attr != "wood_attack"
		      && attr != "water_attack"  && attr != "fire_attack"  && attr != "earth_attack" ) {
			message_vision("$N��$nҡ��ҡͷ, ˵��: ��ֻ���Լ���Щ���� damage,gold_attack,wood_attack,water_attack,fire_attack,earth_attack!\n", me, player);
			return 0;
		}*/
		if ( attr != "damage" ) {
			message_vision("$N��$nҡ��ҡͷ, ˵��: ��ֻ���Լ� damage����!\n", me, player);
			return 0;
		}
		if ( attr == "damage" ) {
			original_value = item->query("weapon_prop/damage");
			if (original_value < 0) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: " + item_name + " ��damage��Ȼ�Ǹ�, ����!\n",
				      me, player);
				return 0;
			}
			new_value = original_value + 1;
			item_level = item->query("level");
			//if (new_value > item_level * 50) {
			if (new_value > item_level * 40) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: ���� " + item_name + " Ŀǰ�ĵȼ���˵, ����damage�Ѿ��㹻����!\n",
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
				message_vision("$NͻȻ��������, �������¼���Ѫ!\n", player, me);
				wx_cost = wx_cost / 2;
			}
			if ( player->query("combat_exp") - wx_cost < 100000 ) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: ������ô����ѧ����, ����û�м���Ѫ���°�?\n", me, player);
				return 0;
			}
			if ( (player->query("combat_exp") - wx_cost)/1000 < item->query("wield/daoxing") ) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: ƾ����㾭�飬�޷�������˸߼���������\n", me, player);
				return 0;
			}
			if (provider == me) {
				if (player->query("g_balance") < gold_cost) {
					message_vision("$N��$nҡ��ҡͷ, ˵��: ����Ҫ" + gold_cost + "����Ʊ��Ϊ�����. ����Ǯׯ��û����ô��!\n",
				      	me, player);
					return 0;
				}
				player->add("g_balance", -gold_cost);
				message_vision("$N��$n���˵�ͷ, ˵��: �����˴�����Ǯׯ�еĻ�ͷ��������" + gold_cost + "����Ʊ��Ϊ�����!\n",
				      me, player);
			}
			skill_level = provider->query_skill("forge",1);
			player->add("combat_exp", -wx_cost);
			adjust_player_skills(player);
			if ( random(skill_level + new_value ) >= skill_level ) {
				player->save();
				player->start_busy(1);
				if ( player != provider ) {
					message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�絽" + item_name + "��\n"
					  + "����$n����һ��, ̾��: �군��, Ѫ������!\n$N��ʧ��" + wx_cost + "������\n", player, provider);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                          + item->query("name") + "(" + item->query("id") + ")��" + attr + "����ʧ��, ��ʧ��"
                          + new_value + "����Ʊ" + wx_cost + "����\n");

				}
				else {
					message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�絽" + item_name + "��\n"
					  + "����$N����һ��, ̾��: �군��, Ѫ������!\n$N��ʧ��" + wx_cost + "������\n", player);
				    log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                          + item->query("name") + "(" + item->query("id") + ")��" + attr + "����ʧ��, ��ʧ��"
                          + wx_cost + "����\n");

				}
				return 0;
			}
			item->set_item_attr("weapon_prop/damage", new_value, player);
			player->save();
			player->start_busy(1);
			if ( player != provider ) {
				message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�絽" + item_name + "��\n"
					  + "ֻ��" + item_name + "��������ҫ�۵Ĺ�â!\n$N��ʧ��" + wx_cost + "������, "
					  + item_name + "��damage����������" + new_value + "\n", player, provider);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                      + item->query("name") + "(" + item->query("id") + ")��" + attr + "���Գɹ�, ��ʧ��"
                      + new_value + "����Ʊ" + wx_cost + "����\n");
			}
			else {
				message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�絽" + item_name + "��\n"
					  + "ֻ��" + item_name + "��������ҫ�۵Ĺ�â!\n$N��ʧ��" + wx_cost + "������, "
					  + item_name + "��damage����������" + new_value + "\n", player);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                      + item->query("name") + "(" + item->query("id") + ")��" + attr + "���Գɹ�, ��ʧ��"
                      + wx_cost + "����\n");
			}
			return 1;
		}
		/*if ( attr == "gold_attack" || attr == "wood_attack" || attr == "water_attack"
		     || attr == "fire_attack"  || attr == "earth_attack" ) {
			if (!item->query("weapon_prop/" + attr)) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: " + item_name + " ��û�еõ���Ӧ��ħ������!\n", me, player);
				return 0;
			}
			original_value = item->query("weapon_prop/" + attr);
			if (original_value < 0) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: " + item_name + " ��" + attr + "��Ȼ�Ǹ�, ����!\n",
				      me, player);
				return 0;
			}
			new_value = original_value + 1;
			item_level = item->query("level");
			if (new_value > item_level * 40) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: ���� " + item_name + " Ŀǰ�ĵȼ���˵, ����" + attr + "�Ѿ��㹻����!\n",
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
				message_vision("$NͻȻ��������, �������¼���Ѫ�����缸���ڵ�!\n", player, me);
				wx_cost = wx_cost / 2;
				dx_cost = wx_cost;
			}
			if ( player->query("combat_exp") - wx_cost < 100000 ) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: ������ô����ѧ����, ����û�м���Ѫ���°�?\n", me, player);
				return 0;
			}
			if ( player->query("daoxing") - dx_cost < 100000 ) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: ������ô�����, ���¶�������û�ж����ڵ�?\n", me, player);
				return 0;
			}
			if (provider == me) {
				if (player->query("g_balance") < gold_cost) {
					message_vision("$N��$nҡ��ҡͷ, ˵��: ����Ҫ" + gold_cost + "����Ʊ��Ϊ�����. ����Ǯׯ��û����ô��!\n",
				      	me, player);
					return 0;
				}
				player->add("g_balance", -new_value);
				message_vision("$N��$n���˵�ͷ, ˵��: �����˴�����Ǯׯ�еĻ�ͷ��������" + gold_cost + "����Ʊ��Ϊ�����!\n",
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
					message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�ͼ����ڵ��絽" + item_name + "��\n"
					  + "����$n����һ��, ̾��: �군��, Ѫ�͵���������!\n$N��ʧ��" + wx_cost + "�����к�" + dx_cost
					  + "�����\n", player, provider);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                          + item->query("name") + "(" + item->query("id") + ")��" + attr + "����ʧ��, ��ʧ��"
                          + new_value + "����Ʊ" + wx_cost + "����" + dx_cost + "����\n");
				}
				else {
					message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�ͼ����ڵ��絽" + item_name + "��\n"
					  + "����$N����һ��, ̾��: �군��, Ѫ�͵�������!\n$N��ʧ��" + wx_cost + "�����к�" + dx_cost
					  + "�����\n", player);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                          + item->query("name") + "(" + item->query("id") + ")��" + attr + "����ʧ��, ��ʧ��"
                          + wx_cost + "����" + dx_cost + "����\n");
				}
				return 0;
			}
			item->set_item_attr("weapon_prop/" + attr, new_value, player);
			player->save();
			player->start_busy(1);
			if ( player != provider ) {
				message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�ͼ����ڵ��絽" + item_name + "��\n"
					  + "ֻ��" + item_name + "��������ҫ�۵Ĺ�â!\n$N��ʧ��" + wx_cost + "�����к�" + dx_cost + "�����,"
					  + item_name + "��"+attr+"����������" + new_value + "\n", player, provider);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                      + item->query("name") + "(" + item->query("id") + ")��" + attr + "���Գɹ�, ��ʧ��"
                      + new_value + "����Ʊ" + wx_cost + "����" + dx_cost + "����\n");
			}
			else {
				message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�絽" + item_name + "��\n"
					  + "ֻ��" + item_name + "��������ҫ�۵Ĺ�â!\n$N��ʧ��" + wx_cost + "�����к�" + dx_cost + "�����,"
					  + item_name + "��"+attr+"����������" + new_value + "\n", player);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                      + item->query("name") + "(" + item->query("id") + ")��" + attr + "���Գɹ�, ��ʧ��"
                      + wx_cost + "����" + dx_cost + "����\n");
			}

			return 1;
		}*/
	} else if (item->is_armor() || item->is_acc()) {
		/*if ( attr != "armor" && attr != "gold_defense" && attr != "wood_defense"
		      && attr != "water_defense"  && attr != "fire_defense"  && attr != "earth_defense" ) {
			message_vision("$N��$nҡ��ҡͷ, ˵��: ��ֻ���Լ���Щ���� armor,gold_defense,wood_defense,water_defense,fire_defense,earth_defense!\n", me, player);
			return 0;
		}*/
		if ( attr != "armor" ) {
			message_vision("$N��$nҡ��ҡͷ, ˵��: ��ֻ���Լ� armor ����!\n", me, player);
			return 0;
		}
		if ( attr == "armor" ) {
			original_value = item->query("armor_prop/armor");
			if (original_value < 0) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: " + item_name + " ��armor��Ȼ�Ǹ�, ����!\n",
				      me, player);
				return 0;
			}
			new_value = original_value + 1;
			item_level = item->query("level");
			if (new_value > item_level * 20) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: ���� " + item_name + " Ŀǰ�ĵȼ���˵, ����armor�Ѿ��㹻����!\n",
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
				message_vision("$NͻȻ��������, �������¼���Ѫ!\n", player, me);
				wx_cost = wx_cost / 2;
			}
			if ( player->query("combat_exp") - wx_cost < 100000 ) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: ������ô����ѧ����, ����û�м���Ѫ���°�?\n", me, player);
				return 0;
			}
			if ( (player->query("combat_exp") - wx_cost)/1000 < item->query("wield/daoxing") ) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: ƾ����㾭�飬�޷�������˸߼��ķ��ߣ�\n", me, player);
				return 0;
			}
			if (provider == me) {
				if (player->query("g_balance") < gold_cost) {
					message_vision("$N��$nҡ��ҡͷ, ˵��: ����Ҫ" + gold_cost + "����Ʊ��Ϊ�����. ����Ǯׯ��û����ô��!\n",
				      	me, player);
					return 0;
				}
				player->add("g_balance", -gold_cost);
				message_vision("$N��$n���˵�ͷ, ˵��: �����˴�����Ǯׯ�еĻ�ͷ��������" + gold_cost + "����Ʊ��Ϊ�����!\n",
				      me, player);
			}
			skill_level = provider->query_skill("forge",1);
			player->add("combat_exp", -wx_cost);
			adjust_player_skills(player);
			if ( random(skill_level + new_value ) >= skill_level ) {
				player->save();
				player->start_busy(1);
				if ( player != provider ) {
					message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�絽" + item_name + "��\n"
					  + "����$n����һ��, ̾��: �군��, Ѫ������!\n$N��ʧ��" + wx_cost + "������\n", player, provider);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                          + item->query("name") + "(" + item->query("id") + ")��" + attr + "����ʧ��, ��ʧ��"
                          + new_value + "����Ʊ" + wx_cost + "����\n");
				}
				else {
					message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�絽" + item_name + "��\n"
					  + "����$N����һ��, ̾��: �군��, Ѫ������!\n$N��ʧ��" + wx_cost + "������\n", player);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                          + item->query("name") + "(" + item->query("id") + ")��" + attr + "����ʧ��, ��ʧ��"
                          + wx_cost + "����\n");
				}
				return 0;
			}
			item->set_item_attr("armor_prop/armor", new_value, player);
			player->save();
			player->start_busy(1);
			if ( player != provider ) {
				message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�絽" + item_name + "��\n"
					  + "ֻ��" + item_name + "��������ҫ�۵Ĺ�â!\n$N��ʧ��" + wx_cost + "������, "
					  + item_name + "��armor����������" + new_value + "\n", player, provider);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                      + item->query("name") + "(" + item->query("id") + ")��" + attr + "���Գɹ�, ��ʧ��"
                      + new_value + "����Ʊ" + wx_cost + "����\n");
			}
			else {
				message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�絽" + item_name + "��\n"
					  + "ֻ��" + item_name + "��������ҫ�۵Ĺ�â!\n$N��ʧ��" + wx_cost + "������, "
					  + item_name + "��armor����������" + new_value + "\n", player);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                      + item->query("name") + "(" + item->query("id") + ")��" + attr + "���Գɹ�, ��ʧ��"
                      + wx_cost + "����\n");
			}
			return 1;
		}
		/*if ( attr == "gold_defense" || attr == "wood_defense" || attr == "water_defense"
		     || attr == "fire_defense"  || attr == "earth_defense" ) {
			if (!item->query("armor_prop/" + attr)) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: " + item_name + " ��û����Ƕ��Ӧ��ħ����ʯ!\n", me, player);
				return 0;
			}
			original_value = item->query("armor_prop/" + attr);
			if (original_value < 0) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: " + item_name + " ��" + attr + "��Ȼ�Ǹ�, ����!\n",
				      me, player);
				return 0;
			}
			new_value = original_value + 1;
			item_level = item->query("level");
			if (new_value > item_level * 20) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: ���� " + item_name + " Ŀǰ�ĵȼ���˵, ����" + attr + "�Ѿ��㹻����!\n",
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
				message_vision("$NͻȻ��������, �������¼���Ѫ�����缸���ڵ�!\n", player, me);
				wx_cost = wx_cost / 2;
				dx_cost = wx_cost;
			}
			if ( player->query("combat_exp") - wx_cost < 100000 ) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: ������ô����ѧ����, ����û�м���Ѫ���°�?\n", me, player);
				return 0;
			}
			if ( player->query("daoxing") - dx_cost < 100000 ) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: ������ô�����, ���¶�������û�ж����ڵ�?\n", me, player);
				return 0;
			}
			if (provider == me) {
				if (player->query("g_balance") < gold_cost) {
					message_vision("$N��$nҡ��ҡͷ, ˵��: ����Ҫ" + gold_cost + "����Ʊ��Ϊ�����. ����Ǯׯ��û����ô��!\n",
				      	me, player);
					return 0;
				}
				player->add("g_balance", -gold_cost);
				message_vision("$N��$n���˵�ͷ, ˵��: �����˴�����Ǯׯ�еĻ�ͷ��������" + gold_cost + "����Ʊ��Ϊ�����!\n",
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
					message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�ͼ����ڵ��絽" + item_name + "��\n"
					  + "����$n����һ��, ̾��: �군��, Ѫ�͵���������!\n$N��ʧ��" + wx_cost + "�����к�" + dx_cost
					  + "�����\n", player, provider);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                          + item->query("name") + "(" + item->query("id") + ")��" + attr + "����ʧ��, ��ʧ��"
                          + new_value + "����Ʊ" + wx_cost + "����" + dx_cost + "����\n");
				}
				else {
					message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�ͼ����ڵ��絽" + item_name + "��\n"
					  + "����$N����һ��, ̾��: �군��, Ѫ�͵�������!\n$N��ʧ��" + wx_cost + "�����к�" + dx_cost
					  + "�����\n", player);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                          + item->query("name") + "(" + item->query("id") + ")��" + attr + "����ʧ��, ��ʧ��"
                          + wx_cost + "����" + dx_cost + "����\n");
				}
				return 0;
			}
			item->set_item_attr("armor_prop/" + attr, new_value, player);
			player->save();
			player->start_busy(1);
			if ( player != provider ) {
				message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�ͼ����ڵ��絽" + item_name + "��\n"
					  + "ֻ��" + item_name + "��������ҫ�۵Ĺ�â!\n$N��ʧ��" + wx_cost + "�����к�" + dx_cost + "�����,"
					  + item_name + "��"+attr+"����������" + new_value + "\n", player, provider);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                      + item->query("name") + "(" + item->query("id") + ")��" + attr + "���Գɹ�, ��ʧ��"
                      + new_value + "����Ʊ" + wx_cost + "����" + dx_cost + "����\n");
			}
			else {
				message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�ͼ����ڵ��絽" + item_name + "��\n"
					  + "ֻ��" + item_name + "��������ҫ�۵Ĺ�â!\n$N��ʧ��" + wx_cost + "�����к�" + dx_cost + "�����,"
					  + item_name + "��"+attr+"����������" + new_value + "\n", player);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                      + item->query("name") + "(" + item->query("id") + ")��" + attr + "���Գɹ�, ��ʧ��"
                      + wx_cost + "����" + dx_cost + "����\n");
			}
			return 1;
		}*/
	} else {
		if ( attr != "gold" && attr != "wood" && attr != "water"  && attr != "fire"  && attr != "earth" ) {
			message_vision("$N��$nҡ��ҡͷ, ˵��: ��ֻ���Լ���Щ���� gold,wood,water,fire,earth!\n", me, player);
			return 0;
		}
		if ( attr == "gold" || attr == "wood" || attr == "water"
		     || attr == "fire"  || attr == "earth" ) {
			if (!item->query("effect/" + attr)) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: " + item_name + " û�ж�Ӧ��ħ������!\n", me, player);
				return 0;
			}
			original_value = item->query("effect/" + attr);
			if (original_value < 0) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: " + item_name + " ��" + attr + "��Ȼ�Ǹ�, ����!\n",
				      me, player);
				return 0;
			}
			new_value = original_value + 1;
			if (new_value > 100 ) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: " + item_name + " ��" + attr + "�Ѿ���������!\n",
				      me, player);
				return 0;
			}
			dx_cost = new_value * new_value;
			//if ( item->is_super_stone() )
			//	dx_cost = dx_cost / 2;
			if (dx_cost < 100) dx_cost = 100;
			if ( random(player->query("int") + player->query("kar") + 1000)
			    < ( player->query("int") + player->query("kar") ) ) {
				message_vision("$NͻȻ��������, �������缸���ڵ�!\n", player, me);
				dx_cost = dx_cost / 2;
			}

			if ( player->query("daoxing") - dx_cost < 100000 ) {
				message_vision("$N��$nҡ��ҡͷ, ˵��: ������ô�����, ���¶�������û�ж����ڵ�?\n", me, player);
				return 0;
			}
			if (provider == me) {
				if (player->query("g_balance") < new_value) {
					message_vision("$N��$nҡ��ҡͷ, ˵��: ����Ҫ" + new_value + "����Ʊ��Ϊ�����. ����Ǯׯ��û����ô��!\n",
				      	me, player);
					return 0;
				}
				player->add("g_balance", -new_value);
				message_vision("$N��$n���˵�ͷ, ˵��: �����˴�����Ǯׯ�еĻ�ͷ��������" + new_value + "����Ʊ��Ϊ�����!\n",
				      me, player);
			}
			skill_level = provider->query_skill("alchemy",1);
			player->add("daoxing", -dx_cost);
			adjust_player_skills(player);
			if ( random(skill_level + new_value ) >= skill_level ) {
				player->save();
				player->start_busy(1);
				if ( player != provider ) {
					message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž������ڵ��絽" + item_name + "��\n"
					  + "����$n����һ��, ̾��: �군��, ��������!\n$N��ʧ��" + dx_cost
					  + "�����\n", player, provider);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                          + item->query("name") + "(" + item->query("id") + ")��" + attr + "����ʧ��, ��ʧ��"
                          + new_value + "����Ʊ" + dx_cost + "����\n");
				}
				else {
					message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž������ڵ��絽" + item_name + "��\n"
					  + "����$N����һ��, ̾��: �군��, ��������!\n$N��ʧ��" + dx_cost
					  + "�����\n", player);
					log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                          + item->query("name") + "(" + item->query("id") + ")��" + attr + "����ʧ��, ��ʧ��"
                          + dx_cost + "����\n");
				}

				return 0;
			}
			item->set_item_attr("effect/" + attr, new_value, player);
			player->save();
			player->start_busy(1);
			if ( player != provider ) {
				message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž������ڵ��絽" + item_name + "��\n"
					  + "ֻ��" + item_name + "��������ҫ�۵Ĺ�â!\n$N��ʧ��" + dx_cost + "�����,"
					  + item_name + "��"+attr+"����������" + new_value + "\n", player, provider);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                      + item->query("name") + "(" + item->query("id") + ")��" + attr + "���Գɹ�, ��ʧ��"
                      + new_value + "����Ʊ" + dx_cost + "����\n");
			}
			else {
				message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž������ڵ��絽" + item_name + "��\n"
					  + "ֻ��" + item_name + "��������ҫ�۵Ĺ�â!\n$N��ʧ��" + dx_cost + "�����,"
					  + item_name + "��"+attr+"����������" + new_value + "\n", player);
				log_file("newitem", player->query("name") + "(" + player->query("id") + ") ����"
                      + item->query("name") + "(" + item->query("id") + ")��" + attr + "���Գɹ�, ��ʧ��"
                      + dx_cost + "����\n");
			}
			return 1;
		}
	}
}
  // ��ǿ����
int do_luimprove(string arg) {
	string item_id, attr;
	object player, me;
	player = this_player();
	me = this_object();
	if (!arg || sscanf(arg, "%s on %s", item_id, attr) != 2) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ����������Ʒ������Ҫ�� luimprove <��Ʒid> on <����>!\n", me, player);
		return 1;
	}
	improve(me, player, me, item_id, attr);
	return 1;
}

  // ��ǿ����
int do_selfimprove(string arg) {
	string item_id, attr;
	object player, me;
	player = this_player();
	me = this_object();
	if (!arg || sscanf(arg, "%s on %s", item_id, attr) != 2) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ���Լ�������Ʒ������Ҫ�� selfimprove <��Ʒid> on <����>!\n", me, player);
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
		tell_object(player, "��������æ!\n");
		return 0;
	}
	item = present(item_id, player);
	if (!objectp(item)) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ������û����������!\n", me, player);
		return 0;
	}
	item_name = item->query("name");
	item_id = item->query("id");
	if ( !item->is_newitem() ) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ֻ������װ���ſ�������������Ƕ��ʯ!\n", me, player);
		return 0;
	}
	if (item->query("equipped")) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ���Ƚ����� " + item_name + " ��˵��!\n", me, player);
		return 0;
	}
	if ( !item->is_armor() && !item->is_acc() && !item->is_weapon()) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: " + item_name + " ������һ�����������!\n", me, player);
		return 0;
	}
	if ( item->query("sockets/now") >= item->query("sockets/max")) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: " + item_name + " ���Ѿ�������ʯ��!\n", me, player);
		return 0;
	}
	stone = present(stone_id, player);
	if (!objectp(stone)) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ������û����������!\n", me, player);
		return 0;
	}
	stone_name = stone->query("name");
	stone_id = stone->query("id");
	if ( !stone->is_newitem() ) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ֻ��������Ʒ�ſ��Ա�������Ƕ!\n", me, player);
		return 0;
	}
	if (stone->query("equipped")) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ���Ƚ����� " + item_name + " ��˵��!\n", me, player);
		return 0;
	}
	if ( !stone->is_magic_stone()) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: " + item_name + " ������һ����ʯ!\n", me, player);
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
		message_vision("$N��$nҡ��ҡͷ, ˵��: ������ô����ѧ����, ����û�м���Ѫ���°�?\n", me, player);
		return 0;
	}
	if (provider == me) {
		if (player->query("g_balance") < cost) {
			message_vision("$N��$nҡ��ҡͷ, ˵��: ����Ҫ" + cost + "����Ʊ��Ϊ�����. ����Ǯׯ��û����ô��!\n",
			    	me, player);
			return 0;
		}
		player->add("g_balance", -cost);
		message_vision("$N��$n���˵�ͷ, ˵��: �����˴�����Ǯׯ�еĻ�ͷ��������" + cost + "����Ʊ��Ϊ�����!\n",
			me, player);
	}
	skill_level = provider->query_skill("forge",1);
	player->add("combat_exp", -wx_cost);
	adjust_player_skills(player);
	if ( random(skill_level + item_level * 50) >= skill_level ) {
		player->save();
		player->start_busy(1);
		if ( player != provider ) {
			message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�絽" + item_name + "��"
			  + stone_name + "��\n"
			  + "����$n����һ��, ̾��: �군��, Ѫ������!\n$N��ʧ��" + wx_cost + "������\n", player, provider);
			log_file("newitem", player->query("name") + "(" + player->query("id") + ") ��"
		              + stone->query("name") + "(" + stone->query("id") + ")��Ƕ��"
	                  + item->query("name") + "(" + item->query("id") + ")��ʧ����, ��ʧ��"
                      + cost + "����Ʊ" + wx_cost + "����\n");
		}
		else {
			message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�絽" + item_name + "��"
			  + stone_name + "��\n"
			  + "����$N����һ��, ̾��: �군��, Ѫ������!\n$N��ʧ��" + wx_cost + "������\n", player);
			log_file("newitem", player->query("name") + "(" + player->query("id") + ") ��"
		              + stone->query("name") + "(" + stone->query("id") + ")��Ƕ��"
	                  + item->query("name") + "(" + item->query("id") + ")��ʧ����, ��ʧ��"
                      + wx_cost + "����\n");
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
		message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�絽" + item_name + "��"
			  + stone_name + "��\n"
		  + "ֻ��" + item_name + "��������ҫ�۵Ĺ�â, ��" + stone_name+ "��������һ��!\n$N��ʧ��"
		  + wx_cost + "������\n", player, provider);
		log_file("newitem", player->query("name") + "(" + player->query("id") + ") ��"
		          + stone->query("name") + "(" + stone->query("id") + ")��Ƕ��"
	              + item->query("name") + "(" + item->query("id") + ")�ϳɹ���, ��ʧ��"
                  + cost + "����Ʊ" + wx_cost + "����\n");
	}
	else {
		message_vision("$N�������˼�����, ͻȻ���ǵ�ͨ��, �����۵����Ž�������Ѫ�絽" + item_name + "��"
			  + stone_name + "��\n"
		  + "ֻ��" + item_name + "��������ҫ�۵Ĺ�â, ��" + stone_name+ "��������һ��!\n$N��ʧ��"
		  + wx_cost + "������\n", player);
		log_file("newitem", player->query("name") + "(" + player->query("id") + ") ��"
		          + stone->query("name") + "(" + stone->query("id") + ")��Ƕ��"
	              + item->query("name") + "(" + item->query("id") + ")�ϳɹ���, ��ʧ��"
                  + wx_cost + "����\n");
	}
	destruct(stone);
	return 1;
}

  // Ƕ�뱦ʯ
int do_luembed(string arg) {
	string item_id, stone_id;
	object player, me;
	player = this_player();
	me = this_object();
	if (!arg || sscanf(arg, "%s in %s", stone_id, item_id) != 2) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ������Ƕ��ʯ��Ҫ�� luembed <��ʯid> in <��Ʒid>!\n", me, player);
		return 1;
	}
	embed(me, player, me, item_id, stone_id);
	return 1;
}

  // Ƕ�뱦ʯ
int do_selfembed(string arg) {
	string item_id, stone_id;
	object player, me;
	player = this_player();
	me = this_object();
	if (!arg || sscanf(arg, "%s in %s", stone_id, item_id) != 2) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ���Լ���Ƕ��ʯ��Ҫ�� selfembed <��ʯid> in <��Ʒid>!\n", me, player);
		return 1;
	}
	embed(me, player, player, item_id, stone_id);
	return 1;
}

  // ����
int do_upgrade(string arg) {
	int cost, current_level, max_level,next_level;
	string item_name;
	object player, me, item;
	player = this_player();
	me = this_object();
	if (!arg ) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ��Ʒ��Ҫ�� upgrade <��Ʒid>!\n", me, player);
		return 1;
	}
	if (player->is_busy()) {
		tell_object(player, "��������æ!\n");
		return 1;
	}
	item = present(arg, player);
	if (!objectp(item)) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ������û����������!\n", me, player);
		return 1;
	}
	item_name = item->query("name");
	if ( !item->is_newitem() ) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ֻ������װ���ſ���������������!\n", me, player);
		return 1;
	}
	if (item->query("equipped")) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ���Ƚ����� " + item_name + " ��˵��!\n", me, player);
		return 1;
	}
	if ( !item->is_armor() && !item->is_acc() && !item->is_weapon()) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: " + item_name + " ������һ�����������!\n", me, player);
		return 1;
	}
	current_level = item->query("level");
	next_level = current_level + 1;
	max_level = item->query("max_level");
	if (current_level >= max_level) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: " + item_name + " �Ѿ�û����������Ǳ����!\n", me, player);
		return 1;
	}
	if (item->fight_exp_rate() < 100) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: " + item_name + " û�л����㹻��ս������!\n", me, player);
		return 1;
	}
	//if (item->is_armor())
	//	max_level = max_level / 2;
	cost = next_level*next_level*100;
	if (item->is_armor() || item->is_acc())
		cost = cost / 2;
	if (player->query("g_balance") < cost) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ����Ҫ" + cost + "����Ʊ��Ϊ�����. ����Ǯׯ��û����ô��!\n",
		    	me, player);
		return 1;
	}
	if ( player->query("combat_exp") - cost < 100000 ) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ������ô����ѧ����, ��������װ�����ĵģ�\n", me, player);
		return 0;
	}
	if ( player->query("daoxing") - cost < 100000 ) {
		message_vision("$N��$nҡ��ҡͷ, ˵��: ������ô�����, ���²�������װ�����ĵģ�\n", me, player);
		return 0;
	}
	player->add("g_balance", -cost);
	player->add("combat_exp", -cost);
	player->add("daoxing", -cost);
	adjust_player_skills(player);
	message_vision("$N��$n���˵�ͷ, ˵��: �����˴�����Ǯׯ�еĻ�ͷ��������" + cost + "����Ʊ��Ϊ�����!\n",
		me, player);
	item->set_item_attr("level", current_level + 1, player );
	item->set_item_attr("fight_exp", 0, player );
	item->set_item_attr("op_exp", 0, player );
	player->save();
	message_vision("$N���洺��ض�$n˵��: " + item_name + "�Ѿ�����������!\n",
		me, player);
	log_file("newitem", player->query("name") + "(" + player->query("id") + ") ��"
	           + item->query("name") + "(" + item->query("id") + ")��������" + item->query("level") + "��, ��ʧ��"
               + cost + "����Ʊ\n");
	player->start_busy(1);
	return 1;
}
