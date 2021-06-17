// emotion: created for ywxrzrdtxy, 2007/02

inherit CHARACTER;
inherit F_CLEAN_UP;

#define SMART_WEAPON_SKILL	"smart/weapon_skill"
#define SMART_LAST_TARGET 		"smart/last_target"
#define MAX_SUPPORTED_INT 2147483647
#define FAMILY_FC		"����ɽ���Ƕ�"

int is_smartnpc() {
	return 1;
}

// pick a possible target in fighting, can be overriden by children
object pick_enemy_target() {
	object* enemies;
	object target;
	int num, i,lower_power, busy_flag, player_flag;

	  // focus on one target, until it is destroyed
	target = query(SMART_LAST_TARGET);
	if ( objectp(target) && is_fighting(target)  )
		return target;

	enemies = query_enemy();
	num = sizeof(enemies);
	if (!num)
		return 0;

	target = 0;
	lower_power = MAX_SUPPORTED_INT;
	busy_flag = 0;
	player_flag = 0;

	// pick a weakest or a busy target, human player takes precedence
	for (i=0;i<num;i++) {
		object t;
		int tmp_power, tmp_busy, tmp_player;
		t = enemies[i];
		tmp_power = t->query("combat_exp")/2 + t->query("daoxing")/2;
		tmp_busy = t->is_busy();
		tmp_player = userp(t);
		if ( !tmp_player && player_flag )
			continue;  // human player takes precedence over NPC
		else if ( tmp_player && !player_flag ) {
			    // human player takes precedence over NPC
			target = t;
			lower_power = tmp_power;
			busy_flag = tmp_busy;
			player_flag = tmp_player;
		} else if (tmp_player && player_flag && random(2)) {
			  // randomly pick a human player
			target = t;
			break;
		} else if ( (tmp_player && player_flag) || (!tmp_player && !player_flag) ) {
			  // compare two human players, or two NPCs
			if ( !tmp_busy && busy_flag )
				continue;  // busy status takes precedence
			else if ( (!tmp_busy && !busy_flag) || ( tmp_busy && busy_flag ) ) {
				// power determines
				if ( lower_power <= tmp_power )
					continue;
				else {
					target = t;
					lower_power = tmp_power;
					busy_flag = tmp_busy;
					player_flag = tmp_player;
				}
			} else if ( tmp_busy && !busy_flag ) {
				// busy status takes precedence
				target = t;
				lower_power = tmp_power;
				busy_flag = tmp_busy;
				player_flag = tmp_player;
			}  else {
				error("something is wrong here");
			}
		} else {
			error("something is wrong here");
		}
	}
	set(SMART_LAST_TARGET, target);
	return target;
}

// main driver of NPC actions
int chat()
{
	string *msg;
	int chance, rnd;

	if( !environment() ) return 0;

	if( !chance = (int)query(is_fighting()? "chat_chance_combat": "chat_chance") )
		return 0;

	if( arrayp(msg = query(is_fighting()? "chat_msg_combat": "chat_msg"))) {
		if( random(100) < chance ) {
			rnd = random(sizeof(msg));
			if( stringp(msg[rnd]) )
				say(msg[rnd]);
			else if( functionp(msg[rnd]) )
				return evaluate(msg[rnd]);
		}
		return 1;
	}
}

// set skills according to the family
void set_family_skill(string family) {
	  // set basic skills
	set_skill("literate", 1);
	set_skill("unarmed", 1);
	set_skill("dodge", 1);
    set_skill("parry", 1);
    set_skill("spells", 1);
    set_skill("force", 1);
	switch(family) {
		case FAMILY_FC:
			create_family("����ɽ���Ƕ�", 1, "��ʦ");
			set("class", "taoist");
			set_skill("puti-zhi", 1);
			map_skill("unarmed", "puti-zhi");
			set_skill("jindouyun", 1);
			map_skill("dodge", "jindouyun");
			set_skill("qianjun-bang", 1);
			map_skill("parry", "qianjun-bang");
			set_skill("dao", 1);
			map_skill("spells", "dao");
			set_skill("wuxiangforce", 1);
			map_skill("force", "wuxiangforce");
			set_skill("stick", 1);
			map_skill("stick", "qianjun-bang");
			set(WEAPON_SKILL, "stick");
			set(WEAPON_SKILL_IDX, 0);
			set("fangcun/panlong_accept","done");  // for ������ʽ
			set("fangcun/panlong_qiansi_finish",1);  // for ������ʽ
			break;
		default:
			error("received an unknown family: " + family)
			break;
	}
}