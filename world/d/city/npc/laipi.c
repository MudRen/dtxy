#include <ansi.h>

inherit NPC;

int ask_gift();
int ask_exchange();

void create()
{
        set_name("��Ƥ����", ({ "laipi dawang","laipi"}) );
        set("gender", "����");
        set("age", 15);
	    set("per", 5+random(25));
        set("long","YWX�����˴�����������������Ƥ���ˡ�����Ҳ����·�ӡ�\n");
        set("combat_exp", 50);
        set("daoxing", 50);
        set("attitude", "friendly");
        set("str", 23);
        set("kee", 20000);
        set("max_kee", 20000);
	set("sen", 20000);
        set("max_sen", 20000);
        set("force", 350);
        set("max_force", 350);
        set("force_factor", 0);
        set_skill("unarmed", 50);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("spells", 500);
        set_skill("taiyi", 500);
	map_skill("spells", "taiyi");
	set_temp("apply/gold_attack", 700);
	set_temp("apply/wood_attack", 700);
	set_temp("apply/water_attack", 700);
	set_temp("apply/fire_attack", 700);
	set_temp("apply/earth_attack", 700);
        setup();
}
void init()
{
	object target = this_player();
	if (!userp(target))
		return;
    add_action("do_checkgift","checkgift");
    add_action("do_addgift","addgift");
//    add_action("do_exchange","exchange");

        ::init();
        set("inquiry", ([
		    "gift": (: ask_gift :),
		    //"exchange": (: ask_exchange :),
        ]));
}

int ask_gift() {
	string msg;
	msg = "$n��$N˵: ֻҪ��ϳ�Ǯ, �ҾͿ��԰���������������. ��checkgiftָ��鿴��Ҫ����Ǯ. ��addgiftָ���������ԣ�Ŀǰ����50Ŷ����\n";
	message_vision(msg, this_player(), this_object());
	return 1;
}

int ask_exchange() {
	string msg;
	msg = "$n��$N˵: �����Ǳ��̫���ò������������Ǳ�ܻ�(exchange)�ƽ�. 100��Ǳ�ܻ�1���ƽ�. ÿ�λ�1���Ǳ��. \n";
	message_vision(msg, this_player(), this_object());
	return 1;
}

int validate_gift_arg(string arg) {
	if (arg != "int" && arg != "str" && arg != "con" && arg != "spi" && arg != "per" && arg != "kar"
	     && arg != "cps" && arg != "cor")
		return 0;
	else
		return 1;
}

string get_chinese_gift(string gift) {
	switch(gift) {
		case "int":
			return "����";
			break;
		case "str":
			return "����";
			break;
		case "con":
			return "����";
			break;
		case "spi":
			return "����";
			break;
		case "per":
			return "��ò";
			break;
		case "kar":
			return "��Ե";
			break;
		case "cps":
			return "����";
			break;
		case "cor":
			return "����";
			break;
		default:
			return "����ʶ" + gift;
			break;
	}
}

int get_gift_cost(object player, string gift) {
	int cost;
	cost = player->query(gift);
	cost++;
	cost *= cost * 5;
	return cost;
}

int do_checkgift(string arg)
{
	object player;
	player = this_player();
	if (!arg || !validate_gift_arg(arg) ) {
		message_vision("$n��$N˵: ��Ҫ��checkgift int|str|con|spi|per|kar|cps|cor ������Ҫ����Ǯ���������ĳһ��������\n",
			player, this_object());
		return 1;
	}
	message_vision("$n��$N˵: ��������Ҫ " + get_gift_cost(player, arg) + " ���ƽ�ȥ����1��" + get_chinese_gift(arg)
	        + ". �㵱ǰ��" + get_chinese_gift(arg) + "��" + player->query(arg) + "\n", player, this_object() );
	return 1;
}

int do_addgift(string arg)
{
	object player;
	int balance, cost;
	player = this_player();
	if (!arg || !validate_gift_arg(arg) ) {
		message_vision("$n��$N˵: ��Ҫ��addgift int|str|con|spi|per|kar|cps|cor ���������ĳһ��������\n",
					player, this_object());
		return 1;
	}
	if (player->query(arg) > 49) {
		message_vision("$n��$N˵: Ŀǰ����ָ���ŵ�50���ȿ��Ÿ��ߵ����������ɡ�\n",
                                        player, this_object());
                return 1;
	}
	
	balance = player->query("g_balance");
	cost = get_gift_cost(player, arg);
	if (balance < cost ) {
		do_checkgift( arg);
		message_vision("$n��$N˵: ����Ǯׯ�Ľ�Ʊ����\n", player, this_object());
		return 1;
	}
	player->add("g_balance", -cost);
	player->add(arg, 1);
	player->save();
	message_vision("$n��$N˵: ���" + get_chinese_gift(arg) + "�Ѿ���������, Ǯ��ֱ�Ӵ�Ǯׯ��������\n", player, this_object());
	log_file("laipi", "[" + ctime(time()) + "]  "
                 + player->query("name") + "(" + player->query("id") + ")��" + cost + "�Ž�Ʊȥ����" + arg
	         + "��" + player->query(arg) + "\n" );
	command("rumor " + player->query("name") + "(" + player->query("id") + ")��һ�ʾ޿���" + query("name")
	        + "����������" + get_chinese_gift(arg) );
	return 1;
}

int do_exchange(string arg)
{
	object player, gold;
	int learned_points, potential;
	player = this_player();
	learned_points = player->query("learned_points");
	if ( learned_points < 100000 ) {
		message_vision("$n��$N˵: ���ȰѰ������͸����Ǳ��ѧ����˵!\n", player, this_object());
		return 1;
	}
	potential = player->query("potential");
	if (potential - learned_points < 10000) {
		message_vision("$n��$N˵: ������û��1���Ǳ�ܿ��Ի�Ǯ\n", player, this_object());
		return 1;
	}
	gold = new("/obj/money/gold-cash");
	gold->set_amount(100);
	gold->move(environment(player));
	player->add("potential", -10000);
	player->save();
	message_vision("$n��$N˵: 100�Ž�Ʊ���ӵ�����, �Լ���������\n", player, this_object() );
	log_file("laipi",  "[" + ctime(time()) + "]  "
                 + player->query("name") + "(" + player->query("id") + ")����Ǳ��, ��100gold\n");
	return 1;
}

int accept_fight(object me)
{
        // message_vision("��Ƥ��������$N����������ƨ����ֱ��ɱ���ҵ��ˣ�\n", me);
        return 1;
}

