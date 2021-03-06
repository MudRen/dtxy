#include <ansi.h>

inherit NPC;

int ask_gift();
int ask_exchange();

void create()
{
        set_name("赖皮大王", ({ "laipi dawang","laipi"}) );
        set("gender", "男性");
        set("age", 15);
	    set("per", 5+random(25));
        set("long","YWX人造人大唐西游中最最最赖皮的人。但是也最有路子。\n");
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
	msg = "$n对$N说: 只要你肯出钱, 我就可以帮你提升先天属性. 用checkgift指令查看需要多少钱. 用addgift指令提升属性（目前上限50哦）。\n";
	message_vision(msg, this_player(), this_object());
	return 1;
}

int ask_exchange() {
	string msg;
	msg = "$n对$N说: 你如果潜能太多用不完可以找我用潜能换(exchange)黄金. 100点潜能换1两黄金. 每次换1万点潜能. \n";
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
			return "悟性";
			break;
		case "str":
			return "力量";
			break;
		case "con":
			return "根骨";
			break;
		case "spi":
			return "灵性";
			break;
		case "per":
			return "容貌";
			break;
		case "kar":
			return "福缘";
			break;
		case "cps":
			return "定力";
			break;
		case "cor":
			return "勇气";
			break;
		default:
			return "不认识" + gift;
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
		message_vision("$n对$N说: 你要用checkgift int|str|con|spi|per|kar|cps|cor 来查需要多少钱来增加你的某一先天属性\n",
			player, this_object());
		return 1;
	}
	message_vision("$n对$N说: 你现在需要 " + get_gift_cost(player, arg) + " 两黄金去增加1点" + get_chinese_gift(arg)
	        + ". 你当前的" + get_chinese_gift(arg) + "是" + player->query(arg) + "\n", player, this_object() );
	return 1;
}

int do_addgift(string arg)
{
	object player;
	int balance, cost;
	player = this_player();
	if (!arg || !validate_gift_arg(arg) ) {
		message_vision("$n对$N说: 你要用addgift int|str|con|spi|per|kar|cps|cor 来增加你的某一先天属性\n",
					player, this_object());
		return 1;
	}
	if (player->query(arg) > 49) {
		message_vision("$n对$N说: 目前属性指开放到50，等开放更高的限制再来吧。\n",
                                        player, this_object());
                return 1;
	}
	
	balance = player->query("g_balance");
	cost = get_gift_cost(player, arg);
	if (balance < cost ) {
		do_checkgift( arg);
		message_vision("$n对$N说: 你在钱庄的金票不够\n", player, this_object());
		return 1;
	}
	player->add("g_balance", -cost);
	player->add(arg, 1);
	player->save();
	message_vision("$n对$N说: 你的" + get_chinese_gift(arg) + "已经被提升了, 钱我直接从钱庄里拿走了\n", player, this_object());
	log_file("laipi", "[" + ctime(time()) + "]  "
                 + player->query("name") + "(" + player->query("id") + ")用" + cost + "张金票去增加" + arg
	         + "到" + player->query(arg) + "\n" );
	command("rumor " + player->query("name") + "(" + player->query("id") + ")用一笔巨款买动" + query("name")
	        + "帮他提升了" + get_chinese_gift(arg) );
	return 1;
}

int do_exchange(string arg)
{
	object player, gold;
	int learned_points, potential;
	player = this_player();
	learned_points = player->query("learned_points");
	if ( learned_points < 100000 ) {
		message_vision("$n对$N说: 你先把白素贞送给你的潜能学了再说!\n", player, this_object());
		return 1;
	}
	potential = player->query("potential");
	if (potential - learned_points < 10000) {
		message_vision("$n对$N说: 你现在没有1万点潜能可以换钱\n", player, this_object());
		return 1;
	}
	gold = new("/obj/money/gold-cash");
	gold->set_amount(100);
	gold->move(environment(player));
	player->add("potential", -10000);
	player->save();
	message_vision("$n对$N说: 100张金票我扔地上了, 自己捡起来吧\n", player, this_object() );
	log_file("laipi",  "[" + ctime(time()) + "]  "
                 + player->query("name") + "(" + player->query("id") + ")换了潜能, 得100gold\n");
	return 1;
}

int accept_fight(object me)
{
        // message_vision("赖皮大王看着$N骂道：还打个屁啊，直接杀了我得了！\n", me);
        return 1;
}

