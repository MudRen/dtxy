// BY emotion

#include <ansi.h>
#include <race.h>
#include <armor.h>
#include <weapon.h>
#include <command.h>
#include <condition.h>
inherit NPC;

#define MANMADE "manmade/"
#define POS MANMADE"pos"
#define FOLLOW_PROB MANMADE"follow_prob"
#define KILL_OTHER_PROB MANMADE"kill_other_prob"
#define FIGHT_PROB MANMADE"fight_prob"
#define HEALTHY_LEVEL MANMADE"healthy_level"
#define WEAPON_SKILL MANMADE"weapon_skill"
#define WEAPON_SKILL_IDX MANMADE"weapon_skill_idx"
#define NO_WEAPON_COUNT MANMADE"no_weapon_count"
#define BIRTH MANMADE"birth"
#define USELESS MANMADE"useless"
#define USED_MKS MANMADE"used_mks"
#define DEATH_COUNT MANMADE"death_count"
#define BIRTH_RANK MANMADE"birth_rank"

#define ITEM_TYPE_WEAPON	1
#define ITEM_TYPE_ARMOR		2
#define ITEM_TYPE_UNKNOWN	0

int rzr_recharge_count = 0;  // used by rzr to recharge itself during peaceful time
int rzr_combat_perform_count = 0;
int rzr_previous_level = -1;
int tick = 0;

mapping basic_weapons = ([ "stick":"/d/city/npc/obj/stick.c",
						   "blade":"/d/city/npc/obj/blade.c",
						   "whip":"/d/city/npc/obj/whip.c",
						   "sword":"/d/city/npc/obj/sword.c",
						   "fork":"/d/city/npc/obj/fork.c",
						   "hammer":"/d/city/npc/obj/hammer.c",
						   "axe":"/d/city/npc/obj/axe.c",
						   "spear":"/d/city/npc/obj/spear.c",
						   "staff":"/d/city/npc/obj/staff.c",
                        ]);

  // this is a manmade npc
int is_manmade_npc() {
	return 1;
}

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file()
{
	string id;
	id = query("id");
	if( !stringp(id) ) return 0;
	return sprintf(DATA_DIR "npc/rzr/%s", id);
}

// to allow re-enable this rzr's heart beat
void enable_heart_beat() {
	set_heart_beat(1);
}


int rzr_need_to_die() {
    if ( ( query("combat_exp") + query("daoxing") ) > 26000000 )
        return 1;
    else
        return 0;
}

// return current rzr level
int rzr_get_my_level() {
	int temp;
	temp = query("combat_exp")/2 + query("daoxing")/2;
	if ( temp < 300000 )
		return 0;
	else if ( temp < 600000 )
		return 1;
	else if ( temp < 1200000 )
		return 2;
	else if ( temp < 2400000 )
		return 3;
	else
		return ( 4 + ( temp - 2400000 ) / 1000000 );
}

int rzr_reward_factor() {
    int level, factor;
    level = rzr_get_my_level();
    switch(level) {
        case 0:
            factor = 4;
            break;
        case 1:
            factor = 8;
            break;
        case 2:
            factor = 16;
            break;
        case 3:
            factor = 24;
            break;
        case 4:
        default:
            factor = 32 + level - 4;
            break;
    }
    return factor;
}

// update this rzr's status based on its current skill levels
void update_health() {
	int my_max_force,my_max_manna;
        int increase_above_level_4;
	int current_level;
	int level_gap;
	my_max_force = query_max_force();
	my_max_manna = query_max_mana();

	set("force_factor", my_max_force / 20 );
	if ( my_max_force > query("maximum_force") )
		set("maximum_force", my_max_force);
	set("max_force", query("maximum_force") );
	set("mana_factor", my_max_manna / 20 );
	if ( my_max_manna > query("maximum_mana") )
		set("maximum_mana", my_max_manna);
	set("max_mana", query("maximum_mana") );
        delete("max_gin");
        delete("max_kee");
        delete("max_sen");
	current_level = rzr_get_my_level();
	if ( rzr_previous_level < current_level ) {
        	switch(current_level) {
            		case 0:
                		set("age", 14);
                		set("per", 40 );
                		set("int", 50 );
                		set("str", 40 );
                		set("cor", 40 );
                		set("spi", 40 );
                		set("cps", 40 );
                		set("con", 40 );
                		set("kar", 40 );
                		break;
            		case 1:
                		set("age", 18);
                		set("per", 60 );
                		set("int", 80 );
                		set("str", 60 );
                		set("cor", 60 );
                		set("spi", 60 );
                		set("cps", 60 );
                		set("con", 60 );
                		set("kar", 60 );
                		break;
            		case 2:
                		set("age", 22);
                		set("per", 80 );
                		set("int", 110 );
                		set("str", 80 );
                		set("cor", 80 );
                		set("spi", 80 );
                		set("cps", 80 );
                		set("con", 80 );
                		set("kar", 80 );
                		break;
            		case 3:
                		set("age", 26);
                		set("per", 100 );
                		set("int", 140 );
                		set("str", 100 );
                		set("cor", 100 );
                		set("spi", 100 );
                		set("cps", 100 );
                		set("con", 100 );
                		set("kar", 100 );
                		break;
            		case 4:
            		default:
                		increase_above_level_4 = current_level - 4;
                		set("age", 30);
                		set("per", 120 + 20 * increase_above_level_4 );
                		set("int", 170 + 20 * increase_above_level_4 );
                		set("str", 120 + 20 * increase_above_level_4 );
                		set("cor", 120 + 20 * increase_above_level_4 );
                		set("spi", 120 + 20 * increase_above_level_4 );
                		set("cps", 120 + 20 * increase_above_level_4 );
                		set("con", 120 + 20 * increase_above_level_4 );
                		set("kar", 120 + 20 * increase_above_level_4 );
                		break;
        	}
		level_gap = current_level - rzr_previous_level;
		add_temp("apply/damage", level_gap * 15);
		add_temp("apply/armor", level_gap * 50);
    		add_temp("apply/gold_defense", level_gap * 100);
    		add_temp("apply/wood_defense", level_gap * 100);
    		add_temp("apply/water_defense", level_gap * 100);
    		add_temp("apply/fire_defense", level_gap * 100);
    		add_temp("apply/earth_defense", level_gap * 100);
    		add_temp("apply/gold_attack", level_gap * 100);
    		add_temp("apply/wood_attack", level_gap * 100);
    		add_temp("apply/water_attack", level_gap * 100);
    		add_temp("apply/fire_attack", level_gap * 100);
    		add_temp("apply/earth_attack", level_gap * 100);
    		if ( current_level > 12 )
			set_temp("apply/level", 8);
  		else if (current_level > 4)
			set_temp("apply/level", current_level - 4);
	}
	rzr_previous_level = current_level;
	HUMAN_RACE->update_player_health(this_object());
	set_weight(40000 + (query("str") - 10)* 2000);
}

// improve rzr's skills
void improve_manmade_npc_skills() {
	mapping skills;
	string *skill_names;
	string skill_to_improve;
	int pots_avail, pots_to_spend;
	int i;
	int count;
	pots_avail = query("potential") - query("learned_points");
	if ( pots_avail <= 0 ) return;
	pots_to_spend = pots_avail / 20;
	if ( pots_to_spend < 10 )
		pots_to_spend = 10;
	if ( pots_to_spend > pots_avail )
		pots_to_spend = pots_avail;
	skills = query_skills();
	skill_names = keys(skills);
	skill_to_improve = skill_names[ random(sizeof(skill_names)) ];
	count = 0;
	for ( i = 0; i < pots_to_spend; i++) {
		count++;
		if ( count > 100 ) {
			reset_eval_cost();
			count = 0;
		}
		improve_skill(skill_to_improve, query_int());
	}
	add("learned_points", pots_to_spend);
	update_health();
	if ( JJ_MANMADE_NPCD->is_debug_learn() )
		    JJ_MANMADE_NPCD->debug_msg( query("name") + " ���� " + pots_to_spend
		                                + " ��Ǳ��ȥ��� " + skill_to_improve );
}

  	// detect the type of the object. if weapon return 1, if armor return 2, otherwise return 0
int get_item_type(object ob) {
	if ( mapp( ob->query("weapon_prop") ) )
		return ITEM_TYPE_WEAPON;  // weapon
	else if ( mapp( ob->query("armor_prop") ) )
		return ITEM_TYPE_ARMOR;
	else
		return ITEM_TYPE_UNKNOWN;
}

	// get the prop sum from a weapon or an armor
int get_prop_sum(object ob) {
	int sum = 0;
	int i;
	string prop_str;
	mapping props;
	mixed* prop_values;

	int type;
	if (!objectp(ob))
		return 0;
	type = get_item_type( ob );
	if ( type == ITEM_TYPE_WEAPON )
		prop_str = "weapon_prop";
	else if ( type == ITEM_TYPE_ARMOR )
		prop_str = "armor_prop";
	else
		return 0;

    if (prop_str == "armor_prop" && (ob->query("No_Wear") || ob->query("no_wear") ))
    	return 0;

	props = ob->query( prop_str );
	if ( !mapp( props  ) )
		return 0;

	prop_values = values(props);
	for (i=0; i<sizeof(prop_values); i++)
		sum += (int)prop_values[i];
	return sum;
}

// pick up an item
int rzr_pickup_item(object item) {
	object env;
	string msg;

	if (!objectp(item))
		return 0;

	env = environment( item );

	msg = query("name") + " �� ";
	if ( env->is_corpse() )
		msg += env->query("name") + "��";
	else
		msg += "����";
	msg += " ������ " + item->query("name");
	item->move(this_object());
	if ( environment(item) != this_object() )
		return 0;
	message_vision( msg + "\n", this_object() );
	JJ_MANMADE_NPCD->announce_msg( msg );
	return 1;
}

// swap an new item with the one currently equipped
void change_item(object old_item, object new_item, int new_item_type ) {
	string msg;

	if (rzr_pickup_item(new_item) == 0 )
		return;  // failed to pick up new item

	if (objectp(old_item)) {
		old_item->unequip();
		msg = query("name") + " �����װ���ŵ� " + old_item->query("name");
		message_vision( msg + "\n", this_object() );
		if ( JJ_MANMADE_NPCD->is_debug_item() )
			JJ_MANMADE_NPCD->debug_msg( msg );
		msg = query("name") + " �� " + old_item->query("name") + " �����˵���";
		old_item->move(environment(this_object()));
		message_vision( msg + "\n", this_object() );
		if ( JJ_MANMADE_NPCD->is_debug_item() )
			JJ_MANMADE_NPCD->debug_msg( msg );
	}


	if ( JJ_MANMADE_NPCD->is_debug_item() )
		JJ_MANMADE_NPCD->debug_msg( msg );
	if ( new_item_type == ITEM_TYPE_WEAPON )
		new_item->wield();
	else if ( new_item_type == ITEM_TYPE_ARMOR )
		new_item->wear();
	msg = query("name") + " �� " + new_item->query("name") + " װ��������";
	message_vision( msg + "\n", this_object() );
	if ( JJ_MANMADE_NPCD->is_debug_item() )
		JJ_MANMADE_NPCD->debug_msg( msg );
}

  // enhance one weapon or armor by pts points
void enhance_item(int num_of_victim, int pts) {
	object* my_inv;
	object item;
	int inv_size;
	int item_type;
	string prop_str;
	mapping props;
	string* prop_keys;
	int prop_keys_size;
	string prop_to_improve;
	string msg;
	int i;
        int old_prop;
	    // weapon item get more chance to enhance
	if ( random( 100 ) > 66 ) {
		item = query_temp("weapon");
		if (!item)
			return;
	} else {
		my_inv = all_inventory();
		inv_size = sizeof(my_inv);
		if ( inv_size == 0 )
			return;  // carrying nothing
		item = my_inv[random(inv_size)];  // pick an item to enhance
	}
	if (item->is_newitem())
		return;  // do not enhance newitem
	item_type = get_item_type(item);
	if ( item_type != ITEM_TYPE_WEAPON && item_type != ITEM_TYPE_ARMOR )
		return;  // the item picked this time is not a weapon or armor, wait for next time
	if ( item_type == ITEM_TYPE_WEAPON ) {
		prop_str = "weapon_prop";
		prop_to_improve = "damage";
	} else if ( item_type == ITEM_TYPE_ARMOR ) {
		prop_str = "armor_prop";
		prop_to_improve = "armor";
	} else
		return;  // if reach this statement, there would be a logic error
	props = item->query(prop_str);
	if ( !mapp( props  ) )
		return;
//	prop_keys = keys(props);
//	prop_keys_size = sizeof(prop_keys);
//	if (prop_keys_size == 0 )
//		return;
		// the following for loop is to copy the original value
		// to workaround a likely underlying system bug
//	for ( i = 0; i < prop_keys_size; i++ ) {
//		item->set(prop_str + "/" + prop_keys[i], props[ prop_keys[i] ] );
//	}
//	prop_to_improve = prop_keys[random(prop_keys_size)];
//	if (!intp(old_prop=item->query(prop_str + "/" + prop_to_improve)))
//		return;
	//if (prop_to_improve == "intelligence")
	//	return;
	old_prop = item->query(prop_str + "/" + prop_to_improve);
        if ( old_prop > 180 )
            return;
	item->unequip();
	item->add("rigidity", 2);
	item->add(prop_str + "/" + prop_to_improve, pts);
	add(USED_MKS, num_of_victim);
	if (!item->query("rzr_victim_num")) {
		item->set("name", item->query("name") + "(������" + HIR"Ѫ��"NOR + "����)" );
	}
	item->add("rzr_victim_num", num_of_victim);
	if ( item_type == ITEM_TYPE_WEAPON )
		item->wield();
	else
		item->wear();
	msg = query("name") + "(" + query("id")
	        + ")����" + num_of_victim + "���ܺ��ߵ���Ѫȥ����� " + item->query("name") + " �� "
	        + prop_to_improve + " ����\n";
	message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�" + msg + NOR, users() );
	log_file("rzr_enhance", msg+"\n");
}

// check and get useful items from ground and corpses
// drugs, weapons, armors
void get_useful_items() {
	object my_env;
	object* room_inv_list;
	object* work_inv_list;
	object* corpse_inv_list;
	mapping inv_mapping;
	object item, best_weapon, best_head, best_neck, best_cloth, best_armor, best_surcoat, best_waist,
		   best_wrists, best_shield, best_finger, best_hands, best_boots;
	int best_weapon_sum, best_head_sum, best_neck_sum, best_cloth_sum, best_armor_sum, best_surcoat_sum,
		best_waist_sum, best_wrists_sum, best_shield_sum, best_finger_sum, best_hands_sum, best_boots_sum;
	int i, temp;
	int pos;
	string my_weapon_skill, msg;
	inv_mapping = ([]);
	pos = 1;
	best_weapon_sum = 0;
	best_head_sum = 0;
	best_neck_sum = 0;
	best_cloth_sum = 0;
	best_armor_sum = 0;
	best_surcoat_sum = 0;
	best_waist_sum = 0;
	best_wrists_sum = 0;
	best_shield_sum = 0;
	best_finger_sum = 0;
	best_hands_sum = 0;
	best_boots_sum = 0;
	my_env = environment(this_object());
	my_weapon_skill = query(WEAPON_SKILL);
	if (!my_env)
		return;
	room_inv_list = all_inventory(my_env);
	temp = sizeof( room_inv_list );
	for ( i = 0; i < temp; i++ ) {
		string pos_str;
		item = room_inv_list[i];
		if (item->is_corpse()) {
			corpse_inv_list = all_inventory(item);
			if ( corpse_inv_list ) {
				int j;
				for ( j = 0; j < sizeof(corpse_inv_list); j++ ) {
					pos_str = "pos" + pos;
					inv_mapping += ( [ pos_str : corpse_inv_list[j] ] );
					pos++;
				}
			}
		} else {
			pos_str = "pos" + pos;
			inv_mapping += ( [ pos_str : item ] );
			pos++;
		}
	}
	work_inv_list = values( inv_mapping );
	temp = sizeof( work_inv_list );
	for ( i = 0; i < temp; i++ ) {
		int item_type;
		string item_id;
		item = work_inv_list[i];
		if ( item->query("no_get") )
			continue;
			// pick up drugs
		item_id = item->query("id");
		if ( item_id == "jinchuang yao" || item_id == "hunyuan dan" || item_id == "bulk jinchuang yao"
                     || item_id == "bulk hunyuan dan" || item_id == "gold-cash") {
			rzr_pickup_item(item);
			continue;
		}
		item_type = get_item_type(item);
		if ( item_type == ITEM_TYPE_ARMOR ) {
			int temp_sum = get_prop_sum( item );
			switch(item->query("armor_type")) {
				case TYPE_HEAD:
					if ( temp_sum > best_head_sum ) {
						best_head_sum = temp_sum;
						best_head = item;
					}
					break;
				case TYPE_NECK:
					if ( temp_sum > best_neck_sum ) {
						best_neck_sum = temp_sum;
						best_neck = item;
					}
					break;
				case TYPE_CLOTH:
					if ( temp_sum > best_cloth_sum ) {
						best_cloth_sum = temp_sum;
						best_cloth = item;
					}
					break;
				case TYPE_ARMOR:
					if ( temp_sum > best_armor_sum ) {
						best_armor_sum = temp_sum;
						best_armor = item;
					}
					break;
				case TYPE_SURCOAT:
					if ( temp_sum > best_surcoat_sum ) {
						best_surcoat_sum = temp_sum;
						best_surcoat = item;
					}
					break;
				case TYPE_WAIST:
					if ( temp_sum > best_waist_sum ) {
						best_waist_sum = temp_sum;
						best_waist = item;
					}
					break;
				case TYPE_WRISTS:
					if ( temp_sum > best_wrists_sum ) {
						best_wrists_sum = temp_sum;
						best_wrists = item;
					}
					break;
				case TYPE_SHIELD:
					if ( temp_sum > best_shield_sum ) {
						best_shield_sum = temp_sum;
						best_shield = item;
					}
					break;
				case TYPE_FINGER:
					if ( temp_sum > best_finger_sum ) {
						best_finger_sum = temp_sum;
						best_finger = item;
					}
					break;
				case TYPE_HANDS:
					if ( temp_sum > best_hands_sum ) {
						best_hands_sum = temp_sum;
						best_hands = item;
					}
					break;
				case TYPE_BOOTS:
					if ( temp_sum > best_boots_sum ) {
						best_boots_sum = temp_sum;
						best_boots = item;
					}
					break;
			}  // end of armor switch
		} else if ( item_type == ITEM_TYPE_WEAPON && item->query("skill_type") == my_weapon_skill
							&& !(item->query("flag") & TWO_HANDED)) {
			int temp_sum = get_prop_sum( item );
			best_weapon_sum = temp_sum;
			best_weapon = item;
		}
	}  // end of for loop

		// change weapon
	item = query_temp("weapon");
	temp = get_prop_sum( item );
	if ( best_weapon_sum > temp )
		change_item( item, best_weapon, ITEM_TYPE_WEAPON );

	item = query_temp("armor/"TYPE_HEAD);
	temp = get_prop_sum( item );
	if ( best_head_sum > temp )
		change_item( item, best_head, ITEM_TYPE_ARMOR );

	item = query_temp("armor/"TYPE_NECK);
	temp = get_prop_sum( item );
	if ( best_neck_sum > temp )
		change_item( item, best_neck, ITEM_TYPE_ARMOR );

	item = query_temp("armor/"TYPE_CLOTH);
	temp = get_prop_sum( item );
	if ( best_cloth_sum > temp )
		change_item( item, best_cloth, ITEM_TYPE_ARMOR );

	item = query_temp("armor/"TYPE_ARMOR);
	temp = get_prop_sum( item );
	if ( best_armor_sum > temp )
		change_item( item, best_armor, ITEM_TYPE_ARMOR );

	item = query_temp("armor/"TYPE_SURCOAT);
	temp = get_prop_sum( item );
	if ( best_surcoat_sum > temp )
		change_item( item, best_surcoat, ITEM_TYPE_ARMOR );

	item = query_temp("armor/"TYPE_WAIST);
	temp = get_prop_sum( item );
	if ( best_waist_sum > temp )
		change_item( item, best_waist, ITEM_TYPE_ARMOR );

	item = query_temp("armor/"TYPE_WRISTS);
	temp = get_prop_sum( item );
	if ( best_wrists_sum > temp )
		change_item( item, best_wrists, ITEM_TYPE_ARMOR );

	item = query_temp("armor/"TYPE_SHIELD);
	temp = get_prop_sum( item );
	if ( best_shield_sum > temp )
		change_item( item, best_shield, ITEM_TYPE_ARMOR );

	item = query_temp("armor/"TYPE_FINGER);
	temp = get_prop_sum( item );
	if ( best_finger_sum > temp )
		change_item( item, best_finger, ITEM_TYPE_ARMOR );

	item = query_temp("armor/"TYPE_HANDS);
	temp = get_prop_sum( item );
	if ( best_hands_sum > temp )
		change_item( item, best_hands, ITEM_TYPE_ARMOR );

	item = query_temp("armor/"TYPE_BOOTS);
	temp = get_prop_sum( item );
	if ( best_boots_sum > temp )
		change_item( item, best_boots, ITEM_TYPE_ARMOR );
}


void rzr_announce_suicide(string perform) {
	string msg;
	object me;
	me = this_object();
	msg = "�üһ�, �����˻���! " + RANK_D->query_self_rude(me) + "�� " + perform + " ������ƴ��!";
	command("chat " + msg);
	msg = "׳��! ��[" + environment(me)->query("short") + "], " + me->query("name") + "ʹ��ƴ������ " + perform + " !";
	command("rumor " + msg);
	log_file("rzr_suicide", msg + "\n");
}

void rzr_apply_weapon_skill( object weapon, string new_skill ) {
    weapon->set_temp("rzr_original_use_apply_skill", weapon->query("use_apply_skill"));
    weapon->set_temp("rzr_original_apply_skill_type",weapon->query("apply/skill_type"));
    weapon->set("use_apply_skill", 1);
    weapon->set("apply/skill_type", new_skill);
}

void rzr_restore_weapon_skill( object weapon ) {
    weapon->set("use_apply_skill", weapon->query_temp("rzr_original_apply_skill_type"));
    weapon->set("apply/skill_type", weapon->query_temp("rzr_original_apply_skill_type"));
}

void rzr_cast_spell(string name) {
	object env = environment(this_object());
	if ( env->query("no_magic") || env->query("rzr_no_magic") )
		return;
	cast_spell(name);
}

void rzr_exert_function(string name) {
	object env = environment(this_object());
	if ( env->query("no_exert") || env->query("rzr_no_exert") )
		return;
	exert_function(name);
}

void rzr_perform_action(object weapon, string skill, string action) {
	object env = environment(this_object());
	if ( env->query("no_fight") || env->query("rzr_no_fight") )
		return;
	if ( skill == "unarmed" ) {
		if (objectp(weapon))
			weapon->unequip();
		perform_action(skill, action);
		if (objectp(weapon))
			weapon->wield();
	} else {
		rzr_apply_weapon_skill(weapon, skill);
		perform_action(skill, action);
		rzr_restore_weapon_skill(weapon);
	}
}

void rzr_special_flee() {
	string my_family;
	object current_env;
	current_env = environment(this_object());
	my_family = query("family/family_name");
	switch(my_family) {
		case "����ɽ���Ƕ�":
		case "�¹�":
		case "�Ϻ�����ɽ":
		case "������":
		default:
			break;
		case "���޵ظ�":
			if ( query("mana") < 150 )
				set("mana", 150);
			rzr_cast_spell("townportal");
			if (current_env != environment(this_object())) {
				  // successfully escaped to "/d/death/gate"
				  command("go south");
				  if (is_fighting()) start_busy(3);
			}
			break;
		case "��������":
			if ( query("mana") < 150 )
				set("mana", 150);
			rzr_cast_spell("shuidun");
			if (current_env != environment(this_object())) {
				if (is_fighting()) start_busy(15 + random(20));
			}
			break;
		case "�ݿ�ɽ�޵׶�":
			if (random(2)) {
				if ( query("mana") < 150 )
					set("mana", 150);
				rzr_cast_spell("tudun");
				if (current_env != environment(this_object())) {
					if (is_fighting()) start_busy(3);
				}
			} else {
				if ( query("mana") < 150 )
					set("mana", 150);
				rzr_cast_spell("huanying");
			}
			break;
		case "��ѩɽ":
			if ( query("mana") < 150 )
				set("mana", 150);
			rzr_cast_spell("escape");
			if (current_env != environment(this_object())) {
				if (is_fighting()) start_busy(5 + random(5));
			}
			break;
		case "��ׯ��":
			if ( query("mana") < 401 )
				set("mana", 401);
			set("faith", 600);
			rzr_cast_spell("qiankun");
			break;
		case "��ɽ��":
			if ( query("mana") < 150 )
				set("mana", 150);
			rzr_cast_spell("tuoqiao");
			if (current_env != environment(this_object())) {
				if (is_fighting()) start_busy(3);
			}
			break;
		case "����ɽ���鶴":
			if ( query("mana") < 150 )
				set("mana", 150);
			rzr_cast_spell("huodun");
			if (current_env != environment(this_object())) {
				if (is_fighting()) start_busy(3);
			}
			break;
	}
	GO_CMD->do_flee(this_object());
	attack();
}

int rzr_is_dying() {
	string my_family;
	object current_env;
	current_env = environment(this_object());
	my_family = query("family/family_name");

	if ( current_env->query("rzr_flee") ) {
		rzr_special_flee();
		return 1;
	}

	if ( query("kee") < query("max_kee") / 3 || query("sen") < query("max_sen") / 3 ) {
		if ( rzr_get_my_level() >= 4 ) {
			if ( random( 2 ) ) {
				GO_CMD->do_flee(this_object());
					// Do attack or clean up enemy if we have fleed.
				attack();
				return 1;
			}
			else
				rzr_special_flee();
		}
		else {
			GO_CMD->do_flee(this_object());
					// Do attack or clean up enemy if we have fleed.
			attack();
		}
		return 1;
	}
	else {
		if ( ( query("kee") < query("max_kee") * 3 / 5 || query("sen") < query("max_sen") * 3 / 5 )
		     && query("force") < 200 && query("mana") < 200 ) {
			GO_CMD->do_flee(this_object());
			attack();
			return 1;
		}
		else return 0;
	}
}


void rzr_self_heal() {
	string my_family;
	my_family = query("family/family_name");
	if ( !is_fighting() ){
		switch(my_family) {
			case "����ɽ���Ƕ�":
			case "�¹�":
			case "�Ϻ�����ɽ":
			case "���޵ظ�":
			case "��������":
			case "�ݿ�ɽ�޵׶�":
			case "��ѩɽ":
			case "��ׯ��":
			case "���ƶ�":
			case "��˿��":
			case "����ɽ���鶴":
			case "������":
				command("exert heal");
				break;
			case "��ɽ��":
					// no heal exert function
				break;
		}
	} else {

	}
}

void rzr_fix_kee_sen(int times ) {
	int i, flag;
	for ( i = 0; i < times; i++ ) {
		flag = 0;
		if ( query("eff_kee") < query("max_kee") ) {
			rzr_self_heal();
			flag = 1;
		}
		if (!flag)
			break;
	}
	for ( i = 0; i < times; i++ ) {
		flag = 0;
		if ( query("eff_kee") < ( query("max_kee") - 100 ) && present("jinchuang yao", this_object()) ) {
			command("eat jinchuang yao" );
			flag = 1;
		}
		if ( query("eff_sen") < ( query("max_sen") - 100 ) && present("hunyuan dan", this_object())) {
			command("eat hunyuan dan" );
			flag = 1;
		}
		if (!flag)
			break;
	}
}

  // ratio should be number between 1 ~ 100, out of 100
void rzr_recover(int ratio) {
	    // exert refresh, exert recover
	if (ratio < 1 || ratio > 100)
		ratio = 100;
	if ( query("kee") < (query("eff_kee") / 100 * ratio) && query("force") > 100 )
		command("exert recover");
	if ( query("sen") < (query("eff_sen")  / 100 * ratio) && query("force") > 100 )
		command("exert refresh");
}


void rzr_recharge_force_mana(int force_pts, int mana_pts, int times) {
	int i, force, max_force, mana, max_mana;
	int flag;
	flag = 0;
	rzr_recharge_count++;
	if ( rzr_recharge_count > 8 ) {
		rzr_recharge_count = 0;  // rest the count
    	force = query("force");
    	max_force = query("max_force") * times;
    	mana = query("mana");
    	max_mana = query("max_mana") * times;
    	if ( force < max_force ) {
			flag = 1;
			force = force + force_pts;
			if ( force > max_force )
				force = max_force;
			set("force", force);
		}
    	if ( mana < max_mana ) {
			flag = 1;
			mana = mana + mana_pts;
			if ( mana > max_mana )
				mana = max_mana;
			set("mana", mana);
		}
		if ( flag )
			message_vision("ֻ��" + query("name") + "ͻȻ�����غ���һ��, �����ܳ������߲�����,����Ҫ����ؾ�������\n",
			               this_object());
		if ( rzr_get_my_level() >= 2)
			clear_condition(0);
	}
}



void rzr_powerup() {
	string my_family;
	int my_weapon_skill_idx;
	object weapon, temp_weapon;
	my_family = query("family/family_name");
	my_weapon_skill_idx = query(WEAPON_SKILL_IDX);
	weapon = query_temp("weapon");
	switch(my_family) {
		case "����ɽ���Ƕ�":
			if ( !query_temp("jldl") )
				rzr_exert_function("jldl");
			if ( !query_temp("powerup") )
				rzr_exert_function("shenjia");
			break;
		case "�¹�":
			if ( !query_temp("powerup") ) {
				if (objectp(weapon)) {
					rzr_perform_action(weapon, "sword", "wuxue");
				}
			}
			break;
		case "�Ϻ�����ɽ":
			if ( !query_temp("anti_magic") )
				rzr_cast_spell("lianhua");
			break;
		case "���޵ظ�":
			if ( !query_temp("powerup") ) {
				switch(random(2)) {
					case 0:
					default:
						rzr_exert_function("powerup");
						break;
					case 1:
						rzr_exert_function("xianxing");
						break;
				}
			}
			break;
		case "��������":
			if ( !query_temp("powerup") ) {
				rzr_exert_function("shield");
			}
			break;
		case "�ݿ�ɽ�޵׶�":
			if ( !query_temp("wdd_powerup") ) {
				rzr_cast_spell("bianfu");
			}
			break;
		case "��ׯ��":
			/* sanqing-jian is too weak
			if ( objectp(weapon) && !query_temp("jianmang") ) {
				map_skill("sword", "sanqing-jian");
				map_skill("parry", "sanqing-jian");
				rzr_perform_action(weapon, "sword", "jianmang");
			} */
			break;
		case "���ƶ�":
			if ( is_fighting() && objectp(weapon) && !query_temp("pfm_shenli") ) {
				rzr_perform_action(weapon, "stick", "shenli");
			}
			if ( objectp(weapon) && rzr_get_my_level() >= 4 && !query_temp("shenli") ) {
                                map_skill("parry", "huoyun-qiang");
                                map_skill("spear", "huoyun-qiang");
                                rzr_perform_action(weapon, "spear", "huohun");
                                map_skill("parry", "wuyue-spear");
                                map_skill("spear", "wuyue-spear");
			}
			break;
		case "��ɽ��":
			if ( !query_temp("powerup") ) {
				rzr_exert_function("huti");
			}
			if ( !query_temp("zhanqi") ) {
				rzr_exert_function("zhanqi");
			}
			break;
		case "��˿��":
			if (is_fighting() && objectp(weapon) && !query_temp("YSJL_tian") ) {
				rzr_perform_action(weapon, "whip", "tian");
			}
			break;
		case "����ɽ���鶴":
			if (!query_temp("powerup"))
				rzr_exert_function("powerup");
			if (objectp(weapon) && !query_temp("pfmxue") ) {
				map_skill("parry", "huntian-jian");
				map_skill("sword", "huntian-jian");
				rzr_perform_action(weapon, "sword", "xue");
				map_skill("parry", "wugou-jian");
				map_skill("sword", "wugou-jian");
			}
			break;
		case "����ɢ��":
			if (!query_temp("powerup"))
				rzr_exert_function("stone");
			break;
		case "������":
			if (!query_temp("powerup"))
				rzr_exert_function("jingxin");
			if ( objectp(weapon) && !query_temp("bawang")) {
				rzr_perform_action(weapon, "spear", "ba");
			}
			break;
	}
}

  // peaceful level 0: ��ƽʱ�ڳ�ҩ�޲�����, 2��/heartbeat
void rzr_peaceful_level_0() {
	rzr_fix_kee_sen(2);
}

  // peaceful level 1: ���Զ��޸�kee,sen
void rzr_peaceful_level_1() {
	// invoke level 0 function
	rzr_fix_kee_sen(3);
	rzr_recover(100);
}

  // peaceful level 2: ���Զ�����������,��������max_force,max_mana
void rzr_peaceful_level_2() {
	rzr_fix_kee_sen(4);
	rzr_recover(100);
	rzr_recharge_force_mana(100,100,1);
}

  // peaceful level 3: ���Զ�����������,�������� 2*max_force,2*max_mana
void rzr_peaceful_level_3() {
	rzr_fix_kee_sen(5);
	rzr_recover(100);
	rzr_recharge_force_mana(150,150,2);
	rzr_powerup();
}

  // peaceful level 4: ���Զ�����������,�������� 2*max_force,2*max_mana
void rzr_peaceful_level_4() {
	rzr_fix_kee_sen(10 + 2 * ((query("combat_exp") + query("daoxing"))/2 - 2400000 ) / 1000000 );
	reset_eval_cost();
	rzr_recover(100);
	rzr_recharge_force_mana(query("max_force")/4,query("max_mana")/4,2);
	rzr_powerup();
}

// actions invoked when rzr is not in fighting
void manmade_peaceful_actions() {
	int chance;
	string my_family;

	my_family = query("family/family_name");
	rzr_combat_perform_count = 0;  // clear the combat perform counter

	rzr_is_dying();

	chance = random(100);
	  // enhance item
	if ( query("MKS") > query(USED_MKS) + 20 )
			enhance_item(20, 10 + random(10));

	   // improve skills
	improve_manmade_npc_skills();

	  // actions based on different rzr levels
	switch(rzr_get_my_level()) {
		case 0:
				// level 0 behavior
			rzr_peaceful_level_0();
			break;
		case 1:
				// level 1 behavior
				// will fix kee and sen
			rzr_peaceful_level_1();
			break;
		case 2:
			rzr_peaceful_level_2();
			break;
		case 3:
			rzr_peaceful_level_3();
			break;
		case 4:
		default:
			rzr_peaceful_level_4();
			break;
	}
	if ( chance >= 0 && chance < 20 ) {
		if ( rzr_need_to_die() )
			add( DEATH_COUNT, -1 );
		if ( query(DEATH_COUNT) <= 0 ) {
			object* inv;
			int i;
			command("chat ���Ų�����, ���ŵ�һ����į���ָ�������, �ü�į��, �Ҳ�����!");
			log_file("rzr_suicide", ctime(time()) + " " + query("name") + "(" + query("id") + ") committed suicide\n" );
			set("combat_exp", 0);
			set("daoxing", 0);
			inv = all_inventory();
			for ( i = 0; i < sizeof(inv); i++ )
				destruct(inv[i]);
			die();
			return;
		}
		// get useful items before leaving the room
		get_useful_items();
		if (!query_temp("no_move"))
			random_move();
	}
	else if ( chance >= 20 && chance < 30 ) {
		int count;
		object weapon;
		weapon = query_temp("weapon");
		if ( !objectp(weapon) ) {
			count = query(NO_WEAPON_COUNT);
			if ( count > 15 ) {
				    // this npc has been empty handed for too long, give it a weapon
				set( NO_WEAPON_COUNT, 0 );
				if (rzr_get_my_level() >= 2) {
					if ( my_family == "��ѩɽ")
						weapon = new("/d/obj/weapon/blade/handudao-redblue");
				}
				if (!objectp(weapon))
					weapon = new(basic_weapons[query(WEAPON_SKILL)]);
				if (objectp(weapon)) {
					weapon->move(this_object());
					weapon->wield();
					JJ_MANMADE_NPCD->announce_msg(query("name") + " ����� " + weapon->query("name")
								+ "����������" );
				}
			} else
				add( NO_WEAPON_COUNT, 1 );
		} else if (rzr_get_my_level() >= 2) {
			if ( my_family == "��ѩɽ" && weapon->query("id") != "ice blade") {
				weapon->move(environment(this_object()));
                                destruct(weapon);
                                set(NO_WEAPON_COUNT, 1000);
                        }
		}
	}
	else if ( chance >= 80 ) {
		int drug_chance;
		object drug;
		drug_chance = random( 100 );
		if ( drug_chance <= 20 )
			drug = new("/d/obj/drug/jinchuang");
		else if ( drug_chance >20 && drug_chance <= 60 )
			drug = new("/d/obj/drug/hunyuandan");
		else
			return;
		drug->move(this_object());
		if ( JJ_MANMADE_NPCD->is_debug_drug() )
			JJ_MANMADE_NPCD->debug_msg( query("name") + " �����ϳ�����һ" + drug->query("base_unit")
				+ drug->query("name"));
		return;
	}
	else {
	}
}

void rzr_random_perform() {
	string my_family;
	int my_weapon_skill_idx;
	object weapon;

	my_family = query("family/family_name");
	my_weapon_skill_idx = query(WEAPON_SKILL_IDX);
	weapon = query_temp("weapon");
	switch(my_family) {
		case "����ɽ���Ƕ�":
			switch(random(12)) {
				case 0:
				default:
					rzr_cast_spell("dingshen");
					break;
				case 1:
					rzr_cast_spell("fenshen");
					break;
				case 2:
					rzr_cast_spell("invocation");
					break;
				case 3:
					rzr_cast_spell("light");
					break;
				case 4:
					rzr_cast_spell("thunder");
					break;
				case 5:
					if (objectp(weapon))
						rzr_perform_action(weapon, "stick", "pili");
					else
						rzr_perform_action(weapon, "unarmed", "xpt");
					break;
				case 6:
					if (objectp(weapon))
						rzr_perform_action(weapon, "stick", "pili");
					else
						rzr_perform_action(weapon, "unarmed", "xpt");
					break;
				case 7:
					if (objectp(weapon))
						rzr_perform_action(weapon, "stick", "qiankun");
					else
						rzr_perform_action(weapon, "unarmed", "xpt");
					break;
				case 8:
					if (objectp(weapon))
						rzr_perform_action(weapon, "stick", "wu");
					else
						rzr_perform_action(weapon, "unarmed", "xpt");
					break;
				case 9:
					rzr_perform_action(weapon, "unarmed", "xpt");
					break;
				case 10:
					rzr_powerup();
					break;
				case 11:
					rzr_exert_function("shenjia");
					break;
			}
			break;  // end of "����ɽ���Ƕ�"
		case "�¹�":
			switch(random(10)) {
				case 0:
				default:
					rzr_cast_spell("arrow");
					break;
				case 1:
					rzr_cast_spell("invocation");
					break;
				case 2:
					rzr_cast_spell("mihun");
					break;
				case 3:
					rzr_cast_spell("shiyue");
					break;
				case 4:
					rzr_perform_action(weapon, "unarmed", "flower");
					break;
				case 5:
					if (objectp(weapon))
						rzr_perform_action(weapon, "sword", "tian");
					else
						rzr_perform_action(weapon, "unarmed", "flower");
					break;
				case 6:
					rzr_powerup();
					break;
				case 7:
					if (objectp(weapon))
						rzr_perform_action(weapon, "sword", "xiaoyao");
					else
						rzr_perform_action(weapon, "unarmed", "flower");
					break;
				case 8:
					if (objectp(weapon))
						rzr_perform_action(weapon, "whip", "qingwang");
					else
						rzr_perform_action(weapon, "unarmed", "flower");
					break;
				case 9:
					if (objectp(weapon))
						rzr_perform_action(weapon, "whip", "ssxx");
					else
						rzr_perform_action(weapon, "unarmed", "flower");
					break;
			}
			break;  // end of "�¹�"
		case "�Ϻ�����ɽ":
			switch(random(9)) {
				case 0:
				default:
					rzr_cast_spell("bighammer");
					break;
				case 1:
					rzr_cast_spell("jingang");
					break;
				case 2:
					rzr_cast_spell("lianhua");
					break;
				case 3:
					rzr_cast_spell("puducanoe");
					break;
				case 4:
					rzr_perform_action(weapon, "unarmed", "lingxi");
					break;
				case 5:
					rzr_perform_action(weapon, "unarmed", "storm");
					break;
				case 6:
					if (objectp(weapon))
						rzr_perform_action(weapon, "staff", "chaodu");
					else
						rzr_perform_action(weapon, "unarmed", "lingxi");
					break;
				case 7:
					if (objectp(weapon))
						rzr_perform_action(weapon, "staff", "fuhu");
					else
						rzr_perform_action(weapon, "unarmed", "lingxi");
					break;
				case 8:
					if (objectp(weapon))
						rzr_perform_action(weapon, "staff", "pudu");
					else
						rzr_perform_action(weapon, "unarmed", "lingxi");
					break;
			}
			break;  // end of "�Ϻ�����ɽ"
		case "���޵ظ�":
			switch(random(15)) {
				case 0:
				default:
					rzr_cast_spell("canoedizang");
					break;
				case 1:
					rzr_cast_spell("curse");
					break;
				case 2:
					rzr_cast_spell("heiwu");
					break;
				case 3:
					rzr_cast_spell("hunfei");
					break;
				case 4:
					rzr_cast_spell("inferno");
					break;
				case 5:
					rzr_cast_spell("invocation");
					break;
				case 6:
					if (objectp(weapon))
						rzr_perform_action(weapon, "whip", "biluo");
					else
						rzr_perform_action(weapon, "unarmed", "zhua");
					break;
				case 7:
					if (objectp(weapon) && query(WEAPON_SKILL) == "whip" && !query_temp("ldlh"))
						rzr_perform_action(weapon, "whip", "ldlh");
					else
						rzr_perform_action(weapon, "unarmed", "zhua");
					break;
				case 8:
					if (objectp(weapon))
						rzr_perform_action(weapon, "whip", "lunhui");
					else
						rzr_perform_action(weapon, "unarmed", "zhua");
					break;
				case 9:
					if (objectp(weapon))
						rzr_perform_action(weapon, "whip", "three");
					else
						rzr_perform_action(weapon, "unarmed", "zhua");
					break;
				case 10:
					rzr_perform_action(weapon, "unarmed", "zhua");
					break;
				case 11:
					if (objectp(weapon))
						rzr_perform_action(weapon, "stick", "qmly");
					else
						rzr_perform_action(weapon, "unarmed", "zhua");
					break;
				case 12:
					if (objectp(weapon) && query(WEAPON_SKILL) == "sword" && !query_temp("yunwu"))
						rzr_perform_action(weapon, "sword", "yanluo");
					else
						rzr_perform_action(weapon, "unarmed", "zhua");
					break;
				case 13:
					rzr_powerup();
					break;
				case 14:
					rzr_exert_function("sheqi");
					break;

			}
			break;  // end of "���޵ظ�"
		case "��������":
			switch(random(9)) {
				case 0:
				default:
					rzr_cast_spell("freez");
					break;
				case 1:
					rzr_cast_spell("hufa");
					break;
				case 2:
					rzr_cast_spell("water");
					break;
				case 3:
					rzr_perform_action(weapon, "unarmed", "leidong");
					break;
				case 4:
					rzr_perform_action(weapon, "unarmed", "long");
					break;
				case 5:
					rzr_perform_action(weapon, "unarmed", "sheshen");
					break;
				case 6:
					if (objectp(weapon))
						rzr_perform_action(weapon, "fork", "fengbo");
					else
						rzr_perform_action(weapon, "unarmed", "leidong");
					break;
				case 7:
					if (objectp(weapon))
						rzr_perform_action(weapon, "hammer", "break");
					else
						rzr_perform_action(weapon, "unarmed", "leidong");
					break;
				case 8:
					rzr_powerup();
					break;
			}
			break;  // end of "��������"
		case "�ݿ�ɽ�޵׶�":
			switch(random(8)) {
				case 0:
				default:
					rzr_cast_spell("bite");
					break;
				case 1:
					rzr_perform_action(weapon, "unarmed", "duo");
					break;
				case 2:
					rzr_perform_action(weapon, "unarmed", "duzun");
					break;
				case 3:
					if (objectp(weapon))
						rzr_perform_action(weapon, "blade", "diyu");
					else
						rzr_perform_action(weapon, "unarmed", "duzun");
					break;
				case 4:
					if (objectp(weapon))
						rzr_perform_action(weapon, "blade", "pozhan");
					else
						rzr_perform_action(weapon, "unarmed", "duzun");
					break;
				case 5:
					if (objectp(weapon))
						rzr_perform_action(weapon, "sword", "qijian");
					else
						rzr_perform_action(weapon, "unarmed", "duzun");
					break;
				case 6:
					if (objectp(weapon))
						rzr_perform_action(weapon, "sword", "yaowu");
					else
						rzr_perform_action(weapon, "unarmed", "duzun");
					break;
				case 7:
					if (objectp(weapon))
						rzr_perform_action(weapon, "sword", "zxzx");
					else
						rzr_perform_action(weapon, "unarmed", "duzun");
					break;
			}
			break;  // end of "�ݿ�ɽ�޵׶�"
		case "��ѩɽ":
			switch(random(8)) {
				case 0:
				default:
					rzr_cast_spell("hufa");
					break;
				case 1:
					rzr_cast_spell("juanbi");
					break;
				case 2:
					rzr_cast_spell("tuntian");
					break;
				case 3:
					rzr_exert_function("ningxie");
					break;
				case 4:
					rzr_perform_action(weapon, "unarmed", "cuixin");
					break;
				case 5:
					if (objectp(weapon))
						rzr_perform_action(weapon, "blade", "baoxue");
					else
						rzr_perform_action(weapon, "unarmed", "cuixin");
					break;
				case 6:
					if (objectp(weapon) && query(WEAPON_SKILL) == "blade" )
						rzr_perform_action(weapon, "blade", "ningxie");
					else
						rzr_perform_action(weapon, "unarmed", "cuixin");
					break;
				case 7:
					if (objectp(weapon))
						rzr_perform_action(weapon, "sword", "feijian");
					else
						rzr_perform_action(weapon, "unarmed", "cuixin");
					break;
			}
			break;  // end of "��ѩɽ"
		case "��ׯ��":
			switch(random(8)) {
				case 0:
				default:
					rzr_cast_spell("baxian");
					break;
				case 1:
					rzr_cast_spell("sanqing");
					break;
				case 2:
					rzr_cast_spell("zhenhuo");
					break;
				case 3:
					if (objectp(weapon)) {
						map_skill("sword", "xiaofeng-sword");
						map_skill("parry", "xiaofeng-sword");
						rzr_perform_action(weapon, "sword", "huichang");
						/* sanqing-jian is too weak
						map_skill("sword", "sanqing-jian");
						map_skill("parry", "sanqing-jian"); */
					}
					else
						rzr_cast_spell("zhenhuo");
					break;
				case 4:
					if (objectp(weapon)) {
						map_skill("sword", "sanqing-jian");
						map_skill("parry", "sanqing-jian");
						rzr_perform_action(weapon, "sword", "jianmang");
						map_skill("sword", "xiaofeng-sword");
						map_skill("parry", "xiaofeng-sword");
					}
					else
						rzr_cast_spell("zhenhuo");
					break;
				case 5:
					if (objectp(weapon)) {
						map_skill("sword", "sanqing-jian");
						map_skill("parry", "sanqing-jian");
						rzr_perform_action(weapon, "sword", "jianzhang");
						map_skill("sword", "xiaofeng-sword");
						map_skill("parry", "xiaofeng-sword");
					}
					else
						rzr_cast_spell("zhenhuo");
					break;
				case 6:
					if (objectp(weapon)) {
						map_skill("sword", "sanqing-jian");
						map_skill("parry", "sanqing-jian");
						rzr_perform_action(weapon, "sword", "sanqing");
						map_skill("sword", "xiaofeng-sword");
						map_skill("parry", "xiaofeng-sword");
					}
					else
						rzr_cast_spell("zhenhuo");
					break;
				case 7:
					rzr_powerup();
					break;
			}
			break;  // end of "��ׯ��"
		case "���ƶ�":
			switch(random(7)) {
				case 0:
				default:
					rzr_cast_spell("niushi");
					break;
				case 1:
					rzr_cast_spell("sanmei");
					break;
				case 2:
					rzr_perform_action(weapon, "unarmed", "zhangxinlei");
					break;
				case 3:
					if (objectp(weapon))
						rzr_perform_action(weapon, "stick", "baiyun");
					else
						rzr_perform_action(weapon, "unarmed", "zhangxinlei");
					break;
				case 4:
					if (objectp(weapon)) {
						map_skill("parry", "huoyun-qiang");
						map_skill("spear", "huoyun-qiang");
						rzr_perform_action(weapon, "spear", "lihuo");
						map_skill("parry", "wuyue-spear");
						map_skill("spear", "wuyue-spear");
					}
					else
						rzr_perform_action(weapon, "unarmed", "zhangxinlei");
					break;
				case 5:
					if (objectp(weapon)) {
						map_skill("parry", "wuyue-spear");
						map_skill("spear", "wuyue-spear");
						rzr_perform_action(weapon, "spear", "buhui");
					}
					else
						rzr_perform_action(weapon, "unarmed", "zhangxinlei");
					break;
				case 6:
					if (objectp(weapon)) {
						map_skill("parry", "wuyue-spear");
						map_skill("spear", "wuyue-spear");
						rzr_perform_action(weapon, "spear", "fengchan");
					}
					else
						rzr_perform_action(weapon, "unarmed", "zhangxinlei");
					break;
				case 7:
					rzr_powerup();
					break;
			}
			break;  // end of "���ƶ�"
		case "��ɽ��":
			switch(random(12)) {
				case 0:
				default:
					rzr_cast_spell("fu");
					break;
				case 1:
					rzr_cast_spell("jianshen");
					break;
				case 2:
					rzr_cast_spell("shou");
					break;
				case 3:
					rzr_perform_action(weapon, "unarmed", "fenguang");
					break;
				case 4:
					if (objectp(weapon)) {
						map_skill("parry", "canxin-jian");
						map_skill("sword", "canxin-jian");
						set("faith", 510);
						rzr_perform_action(weapon, "sword", "xiangsi");
						map_skill("parry", "yujianshu");
						map_skill("sword", "yujianshu");
					}
					else
						rzr_perform_action(weapon, "unarmed", "fenguang");
					break;
				case 5:
					if (objectp(weapon)) {
						map_skill("parry", "mindsword");
						map_skill("sword", "mindsword");
						rzr_perform_action(weapon, "sword", "jianqi");
						map_skill("parry", "yujianshu");
						map_skill("sword", "yujianshu");
					}
					else
						rzr_perform_action(weapon, "unarmed", "shou");
					break;
				case 6:
					if (objectp(weapon)) {
						map_skill("parry", "mindsword");
						map_skill("sword", "mindsword");
						rzr_perform_action(weapon, "sword", "taohua");
						map_skill("parry", "yujianshu");
						map_skill("sword", "yujianshu");
					}
					else
						rzr_perform_action(weapon, "unarmed", "fenguang");
					break;
				case 7:
					if (objectp(weapon)) {
						map_skill("parry", "mindsword");
						map_skill("sword", "mindsword");
						rzr_perform_action(weapon, "sword", "yujian");
						map_skill("parry", "yujianshu");
						map_skill("sword", "yujianshu");
					}
					else
						rzr_perform_action(weapon, "unarmed", "shou");
					break;
				case 8:
					if (objectp(weapon)) {
						map_skill("parry", "yujianshu");
						map_skill("sword", "yujianshu");
						rzr_perform_action(weapon, "sword", "duanshui");
					}
					else
						rzr_perform_action(weapon, "unarmed", "fenguang");
					break;
				case 9:
					if (objectp(weapon)) {
						map_skill("parry", "yujianshu");
						map_skill("sword", "yujianshu");
						rzr_perform_action(weapon, "sword", "fumo");
					}
					else
						rzr_perform_action(weapon, "unarmed", "shou");
					break;
				case 10:
					if (objectp(weapon)) {
						map_skill("parry", "yujianshu");
						map_skill("sword", "yujianshu");
						rzr_perform_action(weapon, "sword", "wanjian");
					}
					else
						rzr_perform_action(weapon, "unarmed", "fenguang");
					break;
				case 11:
					rzr_powerup();
					break;
			}
			break;  // end of "��ɽ��"
		case "��˿��":
			switch(random(9)) {
				case 0:
				default:
					rzr_cast_spell("wuzhishan");
					break;
				case 1:
					rzr_cast_spell("ziqi");
					break;
				case 2:
					rzr_perform_action(weapon, "unarmed", "lanhua");
					break;
				case 3:
					if (objectp(weapon)) {
						map_skill("parry", "chixin-jian");
						map_skill("sword", "chixin-jian");
						rzr_perform_action(weapon, "sword", "haotan");
					}
					else
						rzr_perform_action(weapon, "unarmed", "lanhua");
					break;
				case 4:
					if (objectp(weapon)) {
						map_skill("parry", "chixin-jian");
						map_skill("sword", "chixin-jian");
						rzr_perform_action(weapon, "sword", "hongyan");
					}
					else
						rzr_cast_spell("wuzhishan");
					break;
				case 5:
					if (objectp(weapon)) {
						map_skill("parry", "chixin-jian");
						map_skill("sword", "chixin-jian");
						rzr_perform_action(weapon, "sword", "qingyun");
					}
					else
						rzr_cast_spell("ziqi");
					break;
				case 6:
					if (objectp(weapon)) {
						map_skill("parry", "qingxia-jian");
						map_skill("sword", "qingxia-jian");
						rzr_perform_action(weapon, "sword", "mantian");
						map_skill("parry", "chixin-jian");
						map_skill("sword", "chixin-jian");
					}
					else
						rzr_perform_action(weapon, "unarmed", "lanhua");
					break;
				case 7:
					if (objectp(weapon)) {
						map_skill("parry", "yinsuo-jinling");
						map_skill("sword", "yinsuo-jinling");
						rzr_perform_action(weapon, "whip", "wang");
						map_skill("parry", "chixin-jian");
						map_skill("sword", "chixin-jian");
					}
					else
						rzr_cast_spell("wuzhishan");
					break;
				case 8:
					rzr_powerup();
					break;
			}
			break;  // end of "��˿��"
		case "����ɽ���鶴":
			switch(random(9)) {
				case 0:
				default:
					rzr_cast_spell("fantian");
					break;
				case 1:
					rzr_cast_spell("hufa");
					break;
				case 2:
					rzr_cast_spell("light");
					break;
				case 3:
					rzr_cast_spell("taiji");
					break;
				case 4:
					rzr_perform_action(weapon, "unarmed", "po");
					break;
				case 5:
					if (objectp(weapon)) {
						map_skill("parry", "huntian-jian");
						map_skill("sword", "huntian-jian");
						rzr_perform_action(weapon, "sword", "lin");
						map_skill("parry", "wugou-jian");
						map_skill("sword", "wugou-jian");
					}
					else
						rzr_perform_action(weapon, "unarmed", "po");
					break;
				case 6:
					if (objectp(weapon)) {
						map_skill("parry", "wugou-jian");
						map_skill("sword", "wugou-jian");
						rzr_perform_action(weapon, "sword", "feixian");
					}
					else
						rzr_cast_spell("fantian");
					break;
				case 7:
					if (objectp(weapon)) {
						map_skill("parry", "wugou-jian");
						map_skill("sword", "wugou-jian");
						rzr_perform_action(weapon, "sword", "fengshen");
					}
					else
						rzr_cast_spell("fantian");
					break;
				case 8:
					rzr_powerup();
					break;
			}
			break;  // end of "����ɽ���鶴"
		case "����ɢ��":
			switch(random(4)) {
				case 0:
				default:
					rzr_cast_spell("gold");
					break;
				case 1:
					rzr_cast_spell("shengsi");
					break;
				case 2:
					if (objectp(weapon)) {
						rzr_perform_action(weapon, "sword", "bishou");
					}
				case 3:
					if (objectp(weapon)) {
						set("bellicosity", 300);
						rzr_perform_action(weapon, "sword", "dunnoname");
					}
			}
			break;  // end of "����ɢ��"
		case "������":
			switch(random(4)) {
				case 0:
				default:
					if (objectp(weapon)) {
						rzr_perform_action(weapon, "spear", "meihua");
					}
					break;
				case 1:
					if (objectp(weapon)) {
						rzr_perform_action(weapon, "mace", "tian");
					}
					break;
				case 2:
					if (objectp(weapon)) {
						rzr_perform_action(weapon, "axe", "sanban");
					}
					break;
				case 3:
					if (objectp(weapon)) {
						map_skill("mace", "wusi-mace");
						rzr_perform_action(weapon, "mace", "andu");
						map_skill("mace", "jinglei-mace");
					}
					break;
			}
			break; // end of "������"
	}
}

void rzr_combat_level_0() {
	if ( random( 100 ) > 20 )
		return;
	rzr_random_perform();
}

void rzr_combat_level_1() {
	if ( random( 100 ) > 40 )
		return;
	rzr_random_perform();
}

void rzr_combat_level_2() {
	rzr_fix_kee_sen(3);
	rzr_recover(85);
	if ( random( 100 ) > 70 )
		return;
	rzr_random_perform();
}

void rzr_combat_level_3() {
	string my_family;
	my_family = query("family/family_name");
	get_useful_items();
	rzr_fix_kee_sen(5);
	rzr_recover(85);
	rzr_powerup();

	rzr_random_perform();
}

void rzr_combat_level_4() {
	string my_family;
	int my_weapon_skill_idx;
	object weapon;
	get_useful_items();
	weapon = query_temp("weapon");
/*	if ( objectp( weapon ) ) {
		if ( weapon->query("rigidity") < 8 )
			weapon->set("rigidity", 8 );
	} */

	my_family = query("family/family_name");
	my_weapon_skill_idx = query(WEAPON_SKILL_IDX);

	rzr_fix_kee_sen(10 + 2 * ((query("combat_exp") + query("daoxing"))/2 - 2400000 ) / 1000000 );
	reset_eval_cost();
	rzr_recover(85);
	rzr_powerup();
	switch(my_family) {
		case "����ɽ���Ƕ�":
			command("cast transfer");  // fc's force is more important than mana
			if ( !objectp(weapon) ) {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_cast_spell("fenshen");
						break;
					case 1:
						rzr_perform_action(weapon, "unarmed", "xpt");
						break;
					case 2:
					case 3:
						break;
					case 4:
						switch(random(3)) {
							case 0:
							default:
								rzr_cast_spell("light");
								break;
							case 1:
								rzr_cast_spell("thunder");
								break;
							case 2:
								rzr_cast_spell("dingshen");
								break;
						}
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 6 )
					rzr_combat_perform_count = 0;
			} else {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_cast_spell("fenshen");
						break;
					case 1:
						rzr_perform_action(weapon, "stick", "panlong");
						break;
					case 2:
						switch(random(3)) {
							case 0:
							default:
								rzr_cast_spell("light");
								break;
							case 1:
								rzr_cast_spell("thunder");
								break;
							case 2:
								rzr_cast_spell("dingshen");
								break;
						}
						break;
					case 3:
						rzr_perform_action(weapon, "unarmed", "xpt");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 5 )
					rzr_combat_perform_count = 0;
			}
			break;  // end of "����ɽ���Ƕ�"
		case "�¹�":
			/*
			if (rzr_is_dying() && objectp(weapon)) {
				rzr_announce_suicide("�ط罣");
				set("force", 200);
				set("eff_kee", query("kee"));
				rzr_apply_weapon_skill(weapon, "sword");
				perform_action("sword", "huifeng");
				rzr_restore_weapon_skill(weapon);
				return;
			} */
			if ( !objectp(weapon) ) {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "unarmed", "flower");
						break;
					case 1:
						rzr_cast_spell("shiyue");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 1 )
					rzr_combat_perform_count = 0;
				break;

			} else {
				command("cast transfer");  // xuanhu-blade doesn't need mana
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "whip", "ssxx");
						break;
					case 1:
						rzr_perform_action(weapon, "whip", "qingwang");
						break;
					case 2:
						rzr_perform_action(weapon, "blade", "jueqing");
						break;
					case 3:
						rzr_perform_action(weapon, "sword", "tian");
						break;
					case 4:
						rzr_perform_action(weapon, "unarmed", "flower");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 4 )
					rzr_combat_perform_count = 0;
				break;
			}
			break;  // end of "�¹�"
		case "�Ϻ�����ɽ":
			command("cast transfer");
			if ( !objectp(weapon) ) {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "unarmed", "lingxi");
						break;
					case 1:
						rzr_perform_action(weapon, "unarmed", "rulai");
						break;
					case 2:
						rzr_cast_spell("bighammer");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 2 )
					rzr_combat_perform_count = 0;
			} else {
				int temp;
				switch(rzr_combat_perform_count) {
					case 0:
					default:
					 	rzr_perform_action(weapon, "spear", "fmtd");
                                                break;
					case 1:
						rzr_perform_action(weapon, "unarmed", "lingxi");
						break;
					case 2:
						rzr_perform_action(weapon, "unarmed", "rulai");
						break;
					case 3:
						rzr_cast_spell("bighammer");
						break;
					case 4:
						rzr_perform_action(weapon, "staff", "chaodu");
						break;
					case 5:
						temp = query("bellicosity");
						set("bellicosity", 300);
						rzr_perform_action(weapon, "staff", "pudu");
						set("bellicosity", temp);
						break;
					case 6:
						rzr_cast_spell("bighammer");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 6 )
					rzr_combat_perform_count = 0;
			}
			break;
		case "���޵ظ�":
			command("cast transfer");
			if ( !objectp(weapon) ) {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "unarmed", "zhua");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 0 )
					rzr_combat_perform_count = 0;
			} else {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "unarmed", "zhua");
						break;
					case 1:
						rzr_perform_action(weapon, "sword", "jingtian");
						break;
					case 2:
						rzr_perform_action(weapon, "whip", "xingyun");
						break;
					case 3:
						rzr_perform_action(weapon, "whip", "three");
						break;
					case 4:
						if (query(WEAPON_SKILL) == "sword" && !query_temp("yunwu"))
							rzr_perform_action(weapon, "sword", "yanluo");
						else if (query(WEAPON_SKILL) == "whip" && !query_temp("ldlh"))
							rzr_perform_action(weapon, "whip", "ldlh");
						else
							rzr_perform_action(weapon, "unarmed", "zhua");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 4 )
					rzr_combat_perform_count = 0;
			}
			break;
		case "��������":
			command("cast transfer");
			if ( !objectp(weapon) ) {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "unarmed", "shenglong");
						break;
					case 1:
						rzr_perform_action(weapon, "unarmed", "sheshen");
						break;
					case 2:
						rzr_perform_action(weapon, "unarmed", "leidong");
						break;
					case 3:
						rzr_perform_action(weapon, "unarmed", "long");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 3 )
					rzr_combat_perform_count = 0;
			} else {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "fork", "fengbo");
						break;
					case 1:
						rzr_perform_action(weapon, "fork", "cfpl");
						break;
					case 2:
						rzr_perform_action(weapon, "fork", "fengbo");
						break;
					case 3:
						rzr_perform_action(weapon, "unarmed", "sheshen");
						break;
					case 4:
						rzr_perform_action(weapon, "unarmed", "shenglong");
						break;
					case 5:
						rzr_perform_action(weapon, "unarmed", "leidong");
						break;
					case 6:
						rzr_perform_action(weapon, "hammer", "break");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 6 )
					rzr_combat_perform_count = 0;
			}
			break;
		case "�ݿ�ɽ�޵׶�":
			command("cast transfer");
			if ( !objectp(weapon) ) {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "unarmed", "duzun");
						break;
					case 1:
						rzr_cast_spell("bite");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 1 )
					rzr_combat_perform_count = 0;
			} else {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "blade", "pozhan");
						break;
					case 1:
						if ( query(WEAPON_SKILL) == "blade" && !query_temp("zxzx")) {
							rzr_perform_action(weapon, "blade", "diyu");
						} else if (!query_temp("zxzx")) {
							rzr_perform_action(weapon, "sword", "zxzx");
						} else {
							rzr_perform_action(weapon, "sword", "qijian");
						}
						break;
					case 2:
						rzr_perform_action(weapon, "blade", "xiao");
						break;
					case 3:
						rzr_perform_action(weapon, "sword", "qijian");
						break;
					case 4:
						rzr_perform_action(weapon, "unarmed", "duzun");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 4 )
					rzr_combat_perform_count = 0;
			}
			break;
		case "��ѩɽ":
			if ( !objectp(weapon) ) {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "unarmed", "cuixin");
						break;
					case 1:
						rzr_perform_action(weapon, "unarmed", "cuixin");
						break;
					case 2:
						rzr_cast_spell("tuntian");
						break;
					case 3:
						rzr_cast_spell("niepan");
						break;
					case 4:
						rzr_exert_function("ningxie");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 4 )
					rzr_combat_perform_count = 0;
			} else {
				int temp_force_factor;
				command("cast transfer");
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						temp_force_factor=query("force_factor");
						set("force_factor", query_skill("force")/6);
						rzr_perform_action(weapon, "blade", "piaoxue");
						set("force_factor", temp_force_factor);
						break;
					case 1:
						rzr_perform_action(weapon, "unarmed", "cuixin");
						break;
					case 2:
						rzr_perform_action(weapon, "sword", "feijian");
						break;
					case 3:
						rzr_perform_action(weapon, "blade", "baoxue");
						break;
					case 4:
						rzr_perform_action(weapon, "blade", "ningxie");
						break;
					case 5:
						rzr_exert_function("ningxie");
						break;
					case 6:
						rzr_cast_spell("niepan");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 6 )
					rzr_combat_perform_count = 0;
			}
			break;
		case "��ׯ��":
			if (!present("biyu di", this_object())) {
				object my_xiao;
				my_xiao = new("/d/obj/weapon/sword/yudi");
				my_xiao->set("music/type", "xiao");
				my_xiao->move(this_object());
			}
			command("cast transfer");
			if ( !objectp(weapon) ) {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_cast_spell("sanqing");
						break;
					case 1:
						rzr_perform_action(weapon, "unarmed", "wuxing");
						break;
					case 2:
						rzr_cast_spell("zhenhuo");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 2 )
					rzr_combat_perform_count = 0;
			} else {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						map_skill("sword", "xiaofeng-sword");
						map_skill("parry", "xiaofeng-sword");
						rzr_perform_action(weapon, "blade", "dmyg");
						/*
						map_skill("sword", "sanqing-jian");
						map_skill("parry", "sanqing-jian"); */
						break;
					case 1:
						rzr_cast_spell("sanqing");
						break;
					case 2:
						map_skill("sword", "xiaofeng-sword");
						map_skill("parry", "xiaofeng-sword");
						rzr_perform_action(weapon, "blade", "dmyg");
						/*
						map_skill("sword", "sanqing-jian");
						map_skill("parry", "sanqing-jian"); */
						break;
					case 3:
						rzr_perform_action(weapon, "unarmed", "wuxing");
						break;
					case 4:
						map_skill("sword", "xiaofeng-sword");
						map_skill("parry", "xiaofeng-sword");
						rzr_perform_action(weapon, "sword", "huichang");
						/*
						map_skill("sword", "sanqing-jian");
						map_skill("parry", "sanqing-jian"); */
						break;
/*					case 5:
						map_skill("sword", "sanqing-jian");
						map_skill("parry", "sanqing-jian");
						rzr_perform_action(weapon, "sword", "jianzhang");
						break;
					case 6:
						map_skill("sword", "sanqing-jian");
						map_skill("parry", "sanqing-jian");
						rzr_perform_action(weapon, "sword", "sanqing");
						break; */
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 4 )
					rzr_combat_perform_count = 0;
			}
			break;
		case "���ƶ�":
			command("cast transfer");
			if ( !objectp(weapon) ) {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "unarmed", "zhangxinlei");
						break;
					case 1:
						rzr_cast_spell("sanmei");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 1 )
					rzr_combat_perform_count = 0;
			} else {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "unarmed", "zhangxinlei");
						break;
					case 1:
						map_skill("parry", "huoyun-qiang");
						map_skill("spear", "huoyun-qiang");
						rzr_perform_action(weapon, "spear", "lihuo");
						map_skill("parry", "wuyue-spear");
						map_skill("spear", "wuyue-spear");
						break;
					case 2:
						map_skill("parry", "wuyue-spear");
						map_skill("spear", "wuyue-spear");
						rzr_perform_action(weapon, "spear", "fengchan");
						break;
					case 3:
						map_skill("parry", "wuyue-spear");
						map_skill("spear", "wuyue-spear");
						rzr_perform_action(weapon, "spear", "buhui");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 3 )
					rzr_combat_perform_count = 0;
			}
			break;
		case "��ɽ��":
			command("cast transfer");
			if ( !objectp(weapon) ) {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "unarmed", "fenguang");
						break;
					case 1:
						rzr_cast_spell("jianshen");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 1 )
					rzr_combat_perform_count = 0;
			} else {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						map_skill("parry", "yujianshu");
						map_skill("sword", "yujianshu");
						rzr_perform_action(weapon, "sword", "sword");
						break;
					case 1:
						map_skill("parry", "yujianshu");
						map_skill("sword", "yujianshu");
						rzr_perform_action(weapon, "sword", "wanjian");
						break;
					case 2:
						map_skill("parry", "mindsword");
						map_skill("sword", "mindsword");
						rzr_perform_action(weapon, "sword", "yujian");
						map_skill("parry", "yujianshu");
						map_skill("sword", "yujianshu");
						break;
					case 3:
						map_skill("parry", "canxin-jian");
						map_skill("sword", "canxin-jian");
						set("faith", 510);
						rzr_perform_action(weapon, "sword", "xiangsi");
						map_skill("parry", "yujianshu");
						map_skill("sword", "yujianshu");
						break;
					case 4:
						map_skill("parry", "mindsword");
						map_skill("sword", "mindsword");
						rzr_perform_action(weapon, "sword", "taohua");
						map_skill("parry", "yujianshu");
						map_skill("sword", "yujianshu");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 4 )
					rzr_combat_perform_count = 0;
			}
			break;
		case "��˿��":
			command("cast transfer");
			if ( !objectp(weapon) ) {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "unarmed", "lanhua");
						break;
					case 1:
						rzr_cast_spell("wuzhishan");
						break;
					case 2:
						rzr_cast_spell("ziqi");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 2 )
					rzr_combat_perform_count = 0;
			} else {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						map_skill("parry", "yinsuo-jinling");
						map_skill("sword", "yinsuo-jinling");
						rzr_perform_action(weapon, "whip", "wang");
						map_skill("parry", "chixin-jian");
						map_skill("sword", "chixin-jian");
						break;
					case 1:
						rzr_perform_action(weapon, "unarmed", "lanhua");
						break;
					case 2:
						map_skill("parry", "qingxia-jian");
						map_skill("sword", "qingxia-jian");
						rzr_perform_action(weapon, "sword", "mantian");
						map_skill("parry", "chixin-jian");
						map_skill("sword", "chixin-jian");
						break;
					case 3:
						map_skill("parry", "chixin-jian");
						map_skill("sword", "chixin-jian");
						rzr_perform_action(weapon, "sword", "qingyun");
						break;
					case 4:
						map_skill("parry", "chixin-jian");
						map_skill("sword", "chixin-jian");
						rzr_perform_action(weapon, "sword", "hongyan");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 4 )
					rzr_combat_perform_count = 0;
			}
			break;
		case "����ɽ���鶴":
			command("cast transfer");
			if ( !objectp(weapon) ) {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "unarmed", "po");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 0 )
					rzr_combat_perform_count = 0;
			} else {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "unarmed", "po");
						break;
					case 1:
						rzr_perform_action(weapon, "mace", "quzhu");
						break;
					case 2:
						map_skill("parry", "wugou-jian");
						map_skill("sword", "wugou-jian");
						rzr_perform_action(weapon, "sword", "feixian");
						break;
					case 3:
						map_skill("parry", "huntian-jian");
						map_skill("sword", "huntian-jian");
						rzr_perform_action(weapon, "sword", "lin");
						map_skill("parry", "wugou-jian");
						map_skill("sword", "wugou-jian");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 4 )
					rzr_combat_perform_count = 0;
			}
			break;
		case "����ɢ��":
			set("bellicosity", 300);
			if ( !objectp(weapon) ) {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "unarmed", "icefire");
                                                break;
					case 1:
						rzr_cast_spell("gold");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 1 )  // sanxian need to have more idle time to do regular unarmed attack
					rzr_combat_perform_count = 0;
			} else {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "unarmed", "icefire");
                                                break;
					case 1:
						rzr_perform_action(weapon, "sword", "dunnotruth");
						break;
					case 2:
						rzr_perform_action(weapon, "sword", "bishou");
						break;
					case 3:
						rzr_perform_action(weapon, "sword", "dunnoname");
						break;
					case 4:
						rzr_cast_spell("gold");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 4 )
					rzr_combat_perform_count = 0;
			}
			break;
		case "������":
			command("cast transfer");
			if ( !objectp(weapon) ) {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
                        break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 0 )
					rzr_combat_perform_count = 0;
			} else {
				switch(rzr_combat_perform_count) {
					case 0:
					default:
						rzr_perform_action(weapon, "axe", "kai");
                        break;
					case 1:
						rzr_perform_action(weapon, "mace", "tian");
						break;
					case 2:
						rzr_perform_action(weapon, "spear", "meihua");
						break;
					case 3:
						rzr_perform_action(weapon, "axe", "sanban");
						break;
					case 4:
						map_skill("mace", "wusi-mace");
						rzr_perform_action(weapon, "mace", "andu");
						map_skill("mace", "jinglei-mace");
						break;
				}
				rzr_combat_perform_count++;
				if (rzr_combat_perform_count > 4 )
					rzr_combat_perform_count = 0;
			}
			break;
	}
	  // following code is used to prevent bugs in the performs
	if (query("force") < 1)
		set("force", 1);
	if (query("mana") < 1)
		set("mana", 1);
}

void manmade_combat_actions() {
	rzr_recharge_count = 0; // clear the peaceful recharge counter
	rzr_is_dying();
	switch(rzr_get_my_level()) {
		case 0:
			rzr_combat_level_0();
			break;
		case 1:
			rzr_combat_level_1();
			break;
		case 2:
			rzr_combat_level_2();
			break;
		case 3:
			rzr_combat_level_3();
			break;
		case 4:
		default:
			rzr_combat_level_4();
			break;
	}
}

// copied from char.c to fix the no_move effect on rzr
void heart_beat()
{
	int cnd_flag;
	mapping my;
	object ob,room;
	if (!objectp(room=environment())) return;

	// If we are dying because of mortal wounds?
	if( query("eff_kee") < 0 || query("eff_sen") < 0 || query("eff_gin") < 0) {
		remove_all_enemy();
		die();
		return;
	}

	// If we're dying or falling unconcious?
	if( query("kee") < 0 || query("sen") < 0 || query("gin") < 0) {
		remove_all_enemy();
		if( !living(this_object()) ) die();
		else unconcious();
		return;
	}

	// Do attack if we are fighting.
	if( is_busy() ) {
		continue_action();
		// We don't want heart beat be halt eventually, so return here.
		return;
	}

	if ( living(this_object()) ) {
		attack();  // attack or clean up enemy when necessary

		if ( is_fighting() ) {
			manmade_combat_actions();
		}
		else
			manmade_peaceful_actions();
	}

	if( !this_object() ) return;


	if( tick-- > 0  ) return;
	else tick = 5 + random(10);
    if (!room->query("no_time") || this_object()->query_condition("no_pk_time"))
		cnd_flag = update_condition();

	if( !(cnd_flag & CND_NO_HEAL_UP) )
		heal_up();
}


  // return the best weapon or armor from inventory
  // type can be ITEM_TYPE_WEAPON or ITEM_TYPE_ARMOR
mixed get_best_weapon_armor( object target, int type, string subtype ) {
	object* inv;
	object best;
	int biggest_sum = 0;
	int i;
	inv = all_inventory(target);
	for ( i = 0; i < sizeof(inv); i++ ) {
		int sum;
		string item_sub_type;
		object item = inv[i];
		if ( type == ITEM_TYPE_WEAPON )
			item_sub_type = item->query("skill_type");
		else if ( type == ITEM_TYPE_ARMOR )
			item_sub_type = item->query("armor_type");
		if ( get_item_type(item) == type && item_sub_type == subtype ) {
			sum = get_prop_sum(item);
			if ( sum > biggest_sum ) {
				biggest_sum = sum;
				best = item;
			}
		}
	}
	if ( biggest_sum > 0 )
		return best;
	else
		return 0;
}

string test() {
	return "";
}

  // consider whether this manmade NPC itself is healthy or not
int is_healthy() {
	int health_level, qi_level, shen_level, force_level, mana_level;
	health_level = query(HEALTHY_LEVEL);
	qi_level = query("kee") * 100 / query("max_kee");
	shen_level = query("sen") * 100 / query("max_sen");
	force_level = query("force") * 100 / query("max_force");
	mana_level = query("mana") * 100 / query("max_mana");
	if ( qi_level < health_level || shen_level < health_level || force_level < health_level
	     || mana_level < health_level )
	    return 0;  // unhealthy
	else
		return 1;  // healthy

}

  // determine whether this npc can initiate the fight
int can_fight() {
	if ( is_busy() || is_fighting() || query_temp("no_move") )
	    return 0;
	else
	    return 1;
}

void die() {
	int value, gold, silver, coin, factor, exp_factor;
	object money, hyd, killer, me;
    int increase_above_level_4;
    string log_msg;
    me = this_object();
	value = (query("combat_exp")/20 + query("daoxing")/20);
	value = value / 2;
        factor = rzr_reward_factor();
	gold = (value / 10000);
	value -= gold * 10000;
	silver = (value / 100);
	value -= silver * 100;
	coin = value;
	gold *= factor;
	silver *= factor;
	coin *= factor;
	if ( gold > 0 ) {
		money = new("/obj/money/gold-cash");
		money->set_amount(gold);
		money->move(environment(this_object()));
	}
	if ( silver > 0 ) {
		money = new("/obj/money/silver");
		money->set_amount(silver);
		money->move(environment(this_object()));
	}
	if ( coin > 0 ) {
		money = new("/obj/money/coin");
		money->set_amount(coin);
		money->move(environment(this_object()));
	}
	//message_vision( "ž��һ��, ��" + query("name") + "�Ļ������һ�ʾ޿�\n", this_object() );
/*	if (random(100) >= 100 - exp_factor * 3) {
		hyd = new("/d/obj/drug/huanyang");
		hyd->move(environment(this_object()));
		message_vision( "ž��һ��, ��" + query("name") + "�Ļ������һ�Ż�����\n", this_object() );
		command("chat ̫����! �Һò����׸����Ļ�������û�����ü��Ծ͹���!");
	} */
	remove_rzr_file( query("id") );
	killer = query_temp("last_damage_from");
	log_msg = query("family/family_name") + query("name") + "(" + query("id") + ")("
	          + rzr_get_my_level() + "��) �� ";
	if (objectp(killer))
		log_msg += killer->query("name") + "(" + killer->query("id") + ")";
	else
		log_msg += "��֪����˭";
	log_msg += " ɱ����\n";
	log_file("rzr_die", log_msg);
	::die();
}

void kill_ob(object ob) {
    int chance;
    int first_fight;
    first_fight = is_fighting(ob);
    ::kill_ob(ob);
    if ( !living(this_object()) )
	return;
    if (!userp(ob))
	return;
    chance = rzr_get_my_level() - 10;  // rzr level 10 and up has chances to attack first
    if ( chance < 0 )
        return;
    if ( chance > 4 )
        chance = 4;
    if ( random(10) <= chance )  // up to 50% chance
    {
	if ( !first_fight ) {
		if ( is_busy() )	start_busy(1);
		manmade_combat_actions();
		log_file("rzr_first_attack", ctime(time()) + "  " + query("name") + "(" + query("id") +
                         ") launched first attack at " + ob->query("name") + "(" + query("id") + ")\n" );
	}
    }
}

void set_manmade_npc_skills(int family, int level) {
	  // set basic skills
	set_skill("literate", level);
	set_skill("unarmed", level);
	set_skill("dodge", level);
    set_skill("parry", level);
    set_skill("spells", level);
    set_skill("force", level);
      // set family skills
	switch(family) {
		case 0:
		default:
			create_family("����ɽ���Ƕ�", 1, "��");
			set(POS, 1);
			set("title","");
			set("class", "taoist");
			set_skill("puti-zhi", level);
			map_skill("unarmed", "puti-zhi");
			set_skill("jindouyun", level);
			map_skill("dodge", "jindouyun");
			set_skill("qianjun-bang", level);
			map_skill("parry", "qianjun-bang");
			set_skill("dao", level);
			map_skill("spells", "dao");
			set_skill("wuxiangforce", level);
			map_skill("force", "wuxiangforce");
			set_skill("stick", level);
			map_skill("stick", "qianjun-bang");
			set(WEAPON_SKILL, "stick");
			set(WEAPON_SKILL_IDX, 0);
            set("fangcun/panlong_accept","done");  // for ������ʽ
            set("fangcun/panlong_qiansi_finish",1);  // for ������ʽ
			break;
		case 1:
			create_family("�¹�", 1, "����");
			set(POS, 1);
			set("title","");
			set("class", "xian");
			set("gender", "Ů��" );
			set_skill("moonshentong", level);
			map_skill("spells", "moonshentong");
			set_skill("baihua-zhang", level);
			map_skill("unarmed", "baihua-zhang");
        	set_skill("moonforce", level);
        	map_skill("force", "moonforce");
        	set_skill("moondance", level);
        	map_skill("dodge", "moondance");
        	set("jueqing_known", 2);  // for xuanhu-blade jueqing
		set("accept/sun", 1);
			set_skill("sword", level);
			set_skill("snowsword", level);
			map_skill("sword", "snowsword");
            set_skill("whip", level);
            set_skill("jueqingbian", level);
            map_skill("whip", "jueqingbian");
            set_skill("blade", level);
            set_skill("xuanhu-blade", level);
            map_skill("blade", "xuanhu-blade");
        	switch(random(3)) {
				case 0:
				default:
        			map_skill("parry", "snowsword");
        			set(WEAPON_SKILL, "sword");
        			set(WEAPON_SKILL_IDX, 0);
            		break;
            	case 1:
        			map_skill("parry", "jueqingbian");
        			set(WEAPON_SKILL, "whip");
        			set(WEAPON_SKILL_IDX, 1);
            		break;
            	case 2:
        			map_skill("parry", "xuanhu-blade");
        			set(WEAPON_SKILL, "blade");
        			set(WEAPON_SKILL_IDX, 2);
            		break;
			}
			break;  // end of �¹�
		case 2:
			create_family("�Ϻ�����ɽ", 1, "����");
			set(POS, 1);
			set("title","");
			set("class", "bonze");
			set_skill("buddhism", level);
			map_skill("spells", "buddhism");
			set_skill("jienan-zhi", level);
			map_skill("unarmed", "jienan-zhi");
			set_skill("lotusmove", level);
			map_skill("dodge", "lotusmove");
			set_skill("lotusforce", level);
			map_skill("force", "lotusforce");
			set_skill("staff", level);
			set_skill("lunhui-zhang", level);
			map_skill("staff", "lunhui-zhang");
			map_skill("parry", "lunhui-zhang");
			set_skill("spear", level);
			set_skill("huoyun-qiang", level);
			map_skill("spear", "huoyun-qiang");
			set(WEAPON_SKILL, "staff");
			set(WEAPON_SKILL_IDX, 0);
			set("fmtd_known", 2);
			break;  // end of �Ϻ�����ɽ
		case 3:
			create_family("���޵ظ�", 1, "���");
			set(POS, -1);
			set("title","");
			set("class", "youling");
			set_skill("tonsillit", level);
			map_skill("force", "tonsillit");
			set_skill("ghost-steps", level);
			map_skill("dodge", "ghost-steps");
			set_skill("gouhunshu", level);
			map_skill("spells", "gouhunshu");
			set_skill("jinghun-zhang", level);
			map_skill("unarmed", "jinghun-zhang");
			set_skill("whip", level);
			set_skill("hellfire-whip", level);
            map_skill("whip", "hellfire-whip");
			set_skill("sword", level);
			set_skill("zhuihun-sword", level);
            map_skill("sword", "zhuihun-sword");
			set_skill("stick", level);
			set_skill("kusang-bang", level);
            map_skill("stick", "kusang-bang");
			set("jingtian_known", 3);
			switch(random(2)) {
				case 0:
				default:
					map_skill("parry", "hellfire-whip");
                    set(WEAPON_SKILL, "whip");
                    set(WEAPON_SKILL_IDX, 0);
					break;
				case 1:
					map_skill("parry", "zhuihun-sword");
                    set(WEAPON_SKILL, "sword");
                    set(WEAPON_SKILL_IDX, 1);
					break;
				/* kusang-bang is weak
				case 2:
					map_skill("parry", "kusang-bang");
                    set(WEAPON_SKILL, "stick");
                    set(WEAPON_SKILL_IDX, 2);
					break; */
			}
			break;  // end of ���޵ظ�
		case 4:
			create_family("��������", 1, "ˮ��");
			set(POS, 1);
			set("title","");
			set("class","dragon");
			set_skill("seashentong", level);
			map_skill("spells", "seashentong");
			set_skill("dragonfight", level);
			map_skill("unarmed", "dragonfight");
			set_skill("dragonforce", level);
			map_skill("force", "dragonforce");
			set_skill("dragonstep", level);
			map_skill("dodge", "dragonstep");
			set_skill("fork", level);
			set_skill("fengbo-cha", level);
			map_skill("fork", "fengbo-cha");
			set_skill("hammer", level);
			set_skill("huntian-hammer", level);
			map_skill("hammer", "huntian-hammer");
			set("cfpl_known", 2);
			switch(random(2)) {
				case 0:
				default:
					map_skill("parry", "fengbo-cha");
					set(WEAPON_SKILL, "fork");
					set(WEAPON_SKILL_IDX, 0);
					break;
				case 1:
					map_skill("parry", "huntian-hammer");
					set(WEAPON_SKILL, "hammer");
					set(WEAPON_SKILL_IDX, 1);
					break;
			}
			break;  // end of ��������
		case 5:
			create_family("�ݿ�ɽ�޵׶�", 1, "����");
			set(POS, -1);
			set("title","");
			set("class", "yaomo");
			set_skill("yaofa", level);
			map_skill("spells", "yaofa");
			set_skill("lingfu-steps", level);
			map_skill("dodge", "lingfu-steps");
			set_skill("yinfeng-zhua", level);
			map_skill("unarmed", "yinfeng-zhua");
			set_skill("huntian-qigong", level);
			map_skill("force", "huntian-qigong");
			set_skill("blade", level);
			set_skill("kugu-blade", level);
			map_skill("blade", "kugu-blade");
			set_skill("sword", level);
			set_skill("qixiu-jian", level);
  			map_skill("sword", "qixiu-jian");
  			set("daojian_known", 3);
			switch(random(2)) {
				case 0:
				default:
					map_skill("parry", "kugu-blade");
					set(WEAPON_SKILL, "blade");
					set(WEAPON_SKILL_IDX, 0);
					break;
				case 1:
					map_skill("parry", "qixiu-jian");
					set(WEAPON_SKILL, "sword");
					set(WEAPON_SKILL_IDX, 1);
					break;
			}
			break;  // end of �ݿ�ɽ�޵׶�
		case 6:
			create_family("��ѩɽ", 1, "��ʦ");
			set(POS, -1);
			set("title","");
			set("class", "yaomo");
			set_skill("cuixin-zhang", level);
			map_skill("unarmed", "cuixin-zhang");
			set_skill("xiaoyaoyou", level);
			map_skill("dodge", "xiaoyaoyou");
			set_skill("ningxie-force", level);
			map_skill("force", "ningxie-force");
			set_skill("dengxian-dafa", level);
			map_skill("spells", "dengxian-dafa");
			set_skill("sword", level);
			set_skill("bainiao-jian", level);
			map_skill("sword", "bainiao-jian");
			set_skill("blade", level);
			set_skill("bingpo-blade", level);
			map_skill("blade", "bingpo-blade");
			set("piaoxue_known", 3);
			switch(random(1)) {
				case 0:
				default:
					map_skill("parry", "bingpo-blade");
					set(WEAPON_SKILL, "blade");
					set(WEAPON_SKILL_IDX, 1);
					break;
				/* bainiao-jian is weak
				case 1:
					map_skill("parry", "bainiao-jian");
					set(WEAPON_SKILL, "sword");
					set(WEAPON_SKILL_IDX, 0);
					break;
					*/
			}
			break;  // end of ��ѩɽ
		case 7:
			create_family("��ׯ��", 1, "��ʦ");
			set(POS, 1);
			set("title","");
			set("class", "xian");
			set_skill("wuxing-quan", level);
			map_skill("unarmed", "wuxing-quan");
			set_skill("baguazhen", level);
			map_skill("dodge", "baguazhen");
			set_skill("zhenyuan-force", level);
			map_skill("force", "zhenyuan-force");
			set_skill("taiyi", level);
			map_skill("spells", "taiyi");
			set_skill("sword", level);
			set_skill("sanqing-jian", level);
			set_skill("xiaofeng-sword", level);
			map_skill("sword", "xiaofeng-sword");
			map_skill("parry", "xiaofeng-sword");
			set_skill("blade", level);
			set_skill("yange-blade", level);
			map_skill("blade", "yange-blade");
			set_skill("zouxiao", level);
			set(WEAPON_SKILL, "sword");
			set(WEAPON_SKILL_IDX, 0);
			set("wuxing_known", 5);
			set("spell_qiankun_on", 1);
			break;  // end of ��ׯ��
		case 8:
			create_family("���ƶ�", 1, "��");
			set(POS, -1);
			set("title","");
			set("class","yaomo");
        	set_skill("moshenbu", level);
        	map_skill("dodge", "moshenbu");
        	set_skill("moyun-shou", level);
        	map_skill("unarmed", "moyun-shou");
        	set_skill("huomoforce", level);
        	map_skill("force", "huomoforce");
        	set_skill("pingtian-dafa", level);
        	map_skill("spells", "pingtian-dafa");
			set_skill("spear", level);
			set_skill("huoyun-qiang", level);
			set_skill("wuyue-spear", level);
			map_skill("parry", "wuyue-spear");
			map_skill("spear", "wuyue-spear");
			set_skill("stick", level);
			set_skill("dali-bang", level);
			map_skill("stick", "dali-bang");
			set(WEAPON_SKILL, "spear");
			set(WEAPON_SKILL_IDX, 0);
			set("huohun_known", 3);
			break;  // end of ���ƶ�
		case 9:
			create_family("��ɽ��", 1, "��ʦ");
			set(POS, 1);
			set("title","");
			set("class", "xiake");
			set_skill("zixia-shengong", level);
			set_skill("sevensteps", level);
			set_skill("hunyuan-zhang", level);
			set_skill("taoism",level);
			map_skill("spells", "taoism");
			map_skill("dodge", "sevensteps");
			map_skill("force", "zixia-shengong");
			map_skill("unarmed", "hunyuan-zhang");
			set_skill("sword", level);
			set_skill("canxin-jian",level);
			set_skill("mindsword", level);
			set_skill("yujianshu", level);
			map_skill("parry", "yujianshu");
			map_skill("sword", "yujianshu");
			set_skill("mindsword", level);
			set(WEAPON_SKILL, "sword");
			set(WEAPON_SKILL_IDX, 0);
			set( "sword_known", 8);
			break;  // end of ��ɽ��
		case 10:
			create_family("��˿��", 1, "��");
			set(POS, -1);
			set("title","");
			set("class","yaomo");
			set_skill("pansi-dafa", level);
			map_skill("spells", "pansi-dafa");
			set_skill("lanhua-shou", level);
			map_skill("unarmed", "lanhua-shou");
			set_skill("jiuyin-xinjing", level);
			map_skill("force", "jiuyin-xinjing");
			set_skill("yueying-wubu", level);
			map_skill("dodge", "yueying-wubu");
			set_skill("sword", level);
			set_skill("chixin-jian", level);
			map_skill("sword", "chixin-jian");
			set_skill("qingxia-jian", level);
			set_skill("whip", level);
			set_skill("yinsuo-jinling", level);
			map_skill("parry", "yinsuo-jinling");
			map_skill("whip", "yinsuo-jinling");
			set_skill("qin", level);
			set(WEAPON_SKILL, "sword");
			set(WEAPON_SKILL_IDX, 1);
			set("pansi/love_master",1);
			break;  // end of ��˿��
		case 11:
			create_family("����ɽ���鶴", 1, "��");
			set(POS, 1);
			set("title","");
			set("class", "shen");
			set_skill("xuanzong-force", level);
			map_skill("force", "xuanzong-force");
			set_skill("lingyunbu", level);
			map_skill("dodge", "lingyunbu");
			set_skill("kaitian-zhang", level);
			map_skill("unarmed", "kaitian-zhang");
			set_skill("yuxu-spells", level);
			map_skill("spells", "yuxu-spells");
			set_skill("sword", level);
			set_skill("wugou-jian", level);
			map_skill("parry", "wugou-jian");
			map_skill("sword", "wugou-jian");
			set_skill("huntian-jian", level);
			set_skill("mace", level);
			map_skill("mace", "dashen-bian");
			set(WEAPON_SKILL, "sword");
			set(WEAPON_SKILL_IDX, 0);
			set("quzhu_known", 3);
			break;  // end of ����ɽ���鶴
		case 12:
			create_family("����ɢ��", 1, "ʦ��");
			set(POS, 1);
			set("title","");
			set("class","sanxian");
			set_skill("ice_fire_zhang", level);
			map_skill("unarmed", "ice_fire_zhang");
			set_skill("butian-force", level);
			map_skill("force", "butian-force");
			set_skill("binfen-steps", level);
			map_skill("dodge", "binfen-steps");
			set_skill("mysticism", level);
			map_skill("spells", "mysticism");
			set_skill("sword", level);
			set_skill("spysword", level);
			map_skill("parry", "spysword");
			map_skill("sword", "spysword");
			set_skill("whip", level);
			set_skill("wuwei-fuchen", level);
			map_skill("whip", "wuwei-fuchen");
			set(WEAPON_SKILL, "whip");
			set(WEAPON_SKILL_IDX, 0);
			set("icefire_known", 2);
			set("old_flag/jiandao", 10);
			break;  // end of "����ɢ��"
		case 13:
			create_family("������", 1, "��");
			set(POS, 1);
			set("title","");
			set("class","fighter");
			set_skill("changquan", level);
			map_skill("unarmed", "changquan");
			set_skill("lengquan-force", level);
			map_skill("force", "lengquan-force");
			set_skill("yanxing-steps", level);
			map_skill("dodge", "yanxing-steps");
			set_skill("baguazhou", level);
			map_skill("spells", "baguazhou");
			set_skill("spear", level);
			set_skill("bawang-qiang", level);
			map_skill("spear", "bawang-qiang");
			map_skill("parry", "bawang-qiang");
			set_skill("axe", level);
  			set_skill("sanban-axe", level);
  			map_skill("axe", "sanban-axe");
			set_skill("mace", level);
			set_skill("jinglei-mace", level);
			map_skill("mace", "jinglei-mace");
			set_skill("wusi-mace", level);
			set_skill("archery", level);
			set_skill("xuanyuan-archery", level);
			map_skill("archery", "xuanyuan-archery");
			set(WEAPON_SKILL, "spear");
			set(WEAPON_SKILL_IDX, 0);
			set("kai_known", 3);
			break;  // end of "������"

	}
}

void create()
{
	int exp_level, skill_level;
	set( FOLLOW_PROB, 20 );
	set( KILL_OTHER_PROB, 30 );
	set( FIGHT_PROB, 0 );
	set( HEALTHY_LEVEL, random(30) + 50 );
	set( DEATH_COUNT, 6000 );

    set_name("������ " + JJ_MANMADE_NPCD->generate_name(), ({"rzr" + JJ_MANMADE_NPCD->get_next_rzr_id(),
                                                                            "rzr"}));
    set("long", "�����س�, û��û���������\n");
    set("gender", random(2) ? "����" : "Ů��" );
    switch (random(2)) {
		   case 0: set("attitude", "friendly");break;
		   //case 1: set("attitude", "heroism");break;
		   // case 2: set("attitude", "aggressive");break;  // this will autokill user
		   // case 3: set("attitude", "killer");break;
		   default: set("attitude", "friendly");break;
	}
    set("shen_type", 1);
    if ( random(100) >= 60 ) {
		switch( random(7) ) {
	    	default:
	    	case 0:
	    		set(BIRTH_RANK, 1);
	    		exp_level = 300000;
	    		skill_level = 100;
				break;
	    	case 1:
	    		set(BIRTH_RANK, 2);
	    		exp_level = 600000;
	    		skill_level = 150;
				break;
	    	case 2:
	    		set(BIRTH_RANK, 3);
	    		exp_level = 1200000;
	    		skill_level = 200;
				break;
	    	case 3:
	    		set(BIRTH_RANK, 4);
	    		exp_level = 2400000;
	    		skill_level = 250;
				break;
	    	case 4:
	    		set(BIRTH_RANK, 5);
	    		exp_level = 3400000;
	    		skill_level = 300;
				break;
	    	case 5:
	    		set(BIRTH_RANK, 6);
	    		exp_level = 4400000;
	    		skill_level = 350;
				break;
	    	case 6:
	    		set(BIRTH_RANK, 7);
	    		exp_level = 5400000;
	    		skill_level = 400;
				break;
		}
	} else {
		set(BIRTH_RANK, 0);
   		exp_level = 60000;
   		skill_level = 60;
	}

//	exp_level = 20000000;  // testing
//	skill_level = 500;  // testing

    set("combat_exp", exp_level);
	set("daoxing", exp_level);
	set_manmade_npc_skills(random(14), skill_level);
//	set_manmade_npc_skills(12, skill_level);  // testing

	set(NO_WEAPON_COUNT, 101);

    update_health(); // update own health
    set(BIRTH, time());
	setup();
	if ( rzr_get_my_level() >= 2 ) {
		carry_object("/d/city/npc/obj/armor")->wear();
		carry_object("/d/city/npc/obj/pifeng")->wear();
		carry_object("/d/city/npc/obj/shield")->wear();
		carry_object("/d/city/npc/obj/kui")->wear();
		carry_object("/d/city/npc/obj/cloth")->wear();
		carry_object("/d/city/npc/obj/shoes")->wear();
	}
}

void init() {
	object target;
	if ( ( query("bellicosity") / 35) > query("cps") ) {
		set("bellicosity", query("cps") * 35);
	}
	target = this_player();
	if (target->query("name") == query("name") || target->query_temp("invoker") == this_object() )
		return;
	if (target->query("id") == "gongsun daniang")  // npc gongsun daniang performs badao
		return;
	if (target->query("taskguai"))  //rulai guai,can't kill
		return;
	::init();
	if ( userp(target) ) {
		add_action("do_escape", "go");
		add_action("do_spare", "spare");
	}
	if (target->is_character())
	    call_out( "greet_target", 1, target );
}

string rzr_retain_player_item(object player) {
	int item_count;
	object *inv, item;
	inv = all_inventory(player);
	if(sizeof(inv) > 0)	{
		item = inv[random(sizeof(inv))];
		item->move(environment(this_object()));
		if (objectp(item))
			return item->query("name");
		else
			return "";
	} else
		return "";
}

int do_spare(string arg) {
	object player, me;
	string msg;
	me = this_object();
	player = this_player();
	if (!objectp(me) || !objectp(player))
		return 0;
	msg = player->query("name") + "˫ϥһ����ڵ�,���Ŷ�" + me->query("name")
	      + "˵:������������С,���ͷŹ�С����һ�ΰ�";
	message_vision(msg + "\n", player);
	player->command("chat " + msg );
	if (!player->is_killing(me->query("id")) && !me->is_killing(player->query("id"))) {
		msg = me->query("name") + "���˹�����Ц, ��" + player->query("name") + "˵��: "
		    + RANK_D->query_self_rude(me) + "��û��׼��ɱ������ô�͹�����?���ź�Ϳ�˰�?��Ц����";
		message_vision(msg+"\n", me);
		me->command("chat " + msg);
		me->command("chat " + me->query("name") + "���Ű��Ӻݺݵ�����" + player->query("name")
		      + "���Դ�,�־�������,˵��: ���������������������汿��" );
		return 0;
	} else {
		int level;
		int i, target_eff_kee, target_eff_sen;
		string retained_item;
		msg = query("name") + "��" + player->query("name") + "Ц��: ��Ȼ��������" + RANK_D->query_self_rude(me)
		      + "�ͷŹ���� ";
		level = rzr_get_my_level();
		target_eff_kee = player->query("max_kee")/(level + 1);
		target_eff_sen = player->query("max_sen")/(level + 1);
		player->set("eff_kee", target_eff_kee );
		player->set("eff_sen", target_eff_sen );
		player->set("force", 1 );
		player->set("mana", 1 );
		player->set("kee", 1 );
		player->set("sen", 1 );
		player->clear_condition();
		retained_item = "";
		for ( i = 0; i < level; i++ ) {
			string temp;
			temp = rzr_retain_player_item(player);
			if ( temp != "" )
				retained_item += " " + temp;
		}
		if ( retained_item != "" )
			msg += "�����������" + retained_item + " ";
		msg += "��! �Ժ�������ٿ�����! ";
		message_vision(msg + "\n", me);
		log_file("rzr_spare", msg + "\n");
		me->command("chat " + msg);
		msg = me->query("name") + "����һ�Ű�" + player->query("name") + "�ߵ���ջȥ��, ֱ��"
		          + player->query("name") + "ˤ�����˹�ȥ! ";
		message_vision(msg + "\n", me);
		me->command("rumor " + msg);
		remove_killer(player);
		player->remove_killer(this_object());
		player->add("rzr_spare", 1);
		player->move("/d/city/kezhan");
		player->unconcious();
		attack();  // remove enemy
		return 1;
	}
}

int do_escape(string arg)
{
	if ( environment(this_player()) != environment(this_object()))
		return 0;

	if (this_player()->is_fighting(this_object())) {
		int my_level;
		my_level = rzr_get_my_level();
		if ( my_level > 4 ) my_level = 4;
		if (random(10) <= my_level ) {
			message_vision("$Nһ���ֵ�ס��$n��ȥ·,�е�:�ܻ�û�д��������?\n",this_object(), this_player() );
			this_player()->start_busy(1+random(my_level));
    		return 1;
		}
	}
    else
    	return 0;  // let the normal go command handle this
}

void greet_target( object target ) {
	    object me;
	   	int action_flag;   // 0 means look, 1 means kill, 2 means follow and kill, 3 means fight
	    string mymsg;
	    object rob_item;
	    int rob_flag=0;  // whether determined to rob an item from target or not
	    action_flag = 0;

		if (!objectp(target))
			return;
		if (userp(target))
			return;
		if ((environment(target)) != environment(this_object()))
			return;

		if ( !target->is_character() )
			return;

		me = this_object();

		if ( target->query_temp("invoker") == this_object() )
			return;

			// do not kill NPCs who has ask list
		if ( target->query("inquiry") ) {
			if ( JJ_MANMADE_NPCD->is_debug_skip_npc() )
				 JJ_MANMADE_NPCD->debug_msg( query("name") + " ���� " + target->query("name")
				    + "(" + target->query("id") + ")��ask, �����κ��ж�");
			return;
		}

		if ( ( ( target->query( "combat_exp" ) + target->query( "daoxing" ) ) / (rzr_get_my_level() + 1) ) >
			 ( query("combat_exp") + query("daoxing") ) ) {
			if ( JJ_MANMADE_NPCD->is_debug_meet() )
				 JJ_MANMADE_NPCD->debug_msg( query("name") + " ���� " + target->query("name") + "����̫��, �����κ��ж�");
			return;
		}

		if ( JJ_MANMADE_NPCD->is_debug_meet() )
		    JJ_MANMADE_NPCD->debug_msg( me->query("name") + " ������ " + target->query("name") );

		if ( target->is_manmade_npc() && query(POS) != target->query(POS) )
		       action_flag = 1;  // will kill
		else if ( target->is_manmade_npc() == 0 && random(100) <= query(KILL_OTHER_PROB) )
		       action_flag = 1;  // will kill
		else if( random(100) <= query(FIGHT_PROB) )
		       action_flag = 3;  // will fight
		else
		     action_flag = 0; // will look

		if ( action_flag == 1 && random(100) <= query(FOLLOW_PROB) )
		     action_flag = 2;  // will follow and kill

		if ( ( action_flag == 0 || action_flag == 1 || action_flag == 3 ) && !userp(target)
		       && !target->is_manmade_npc() && can_fight() && is_healthy() ) {
			int my_weapon_sum, my_head_sum, my_neck_sum, my_cloth_sum, my_armor_sum, my_surcoat_sum, my_waist_sum,
				my_wrists_sum, my_shield_sum, my_finger_sum, my_hands_sum, my_boots_sum;
			int my_item_sum, target_item_sum;
			string my_weapon_skill;
			int i;
			object* target_inv;
			int target_inv_size;

			rob_flag = 0;  // clear the rob flag

			my_weapon_skill = query(WEAPON_SKILL);

			my_weapon_sum = get_prop_sum(query_temp("weapon"));
			my_head_sum = get_prop_sum(query_temp("armor/"TYPE_HEAD));
			my_neck_sum = get_prop_sum(query_temp("armor/"TYPE_NECK));
			my_cloth_sum = get_prop_sum(query_temp("armor/"TYPE_CLOTH));
			my_armor_sum = get_prop_sum(query_temp("armor/"TYPE_ARMOR));
			my_surcoat_sum = get_prop_sum(query_temp("armor/"TYPE_SURCOAT));
			my_waist_sum = get_prop_sum(query_temp("armor/"TYPE_WAIST));
			my_wrists_sum = get_prop_sum(query_temp("armor/"TYPE_WRISTS));
			my_shield_sum = get_prop_sum(query_temp("armor/"TYPE_SHIELD));
			my_finger_sum = get_prop_sum(query_temp("armor/"TYPE_FINGER));
			my_hands_sum = get_prop_sum(query_temp("armor/"TYPE_HANDS));
			my_boots_sum = get_prop_sum(query_temp("armor/"TYPE_BOOTS));

				// check target weapon
			target_inv = all_inventory(target);
			target_inv_size = sizeof(target_inv);
			for (i = 0; i<target_inv_size;i++) {
				int target_item_type;
				object target_item = target_inv[i];
				//if ( target_item->query(USELESS) )
				//	continue; // this item can not be used by this particular NPC, then skip it
				target_item_type = get_item_type(target_item);
				if ( target_item_type == ITEM_TYPE_ARMOR ) {
					int temp_sum = get_prop_sum( target_item );
					switch(target_item->query("armor_type")) {
						case TYPE_HEAD:
							if ( temp_sum > my_head_sum ) {
								rob_flag = 1;
								my_item_sum = my_head_sum;
							}
							break;
						case TYPE_NECK:
							if ( temp_sum > my_neck_sum ) {
								rob_flag = 1;
								my_item_sum = my_neck_sum;
							}
							break;
						case TYPE_CLOTH:
							if ( temp_sum > my_cloth_sum ) {
								rob_flag = 1;
								my_item_sum = my_cloth_sum;
							}
							break;
						case TYPE_ARMOR:
							if ( temp_sum > my_armor_sum ) {
								rob_flag = 1;
								my_item_sum = my_armor_sum;
							}
							break;
						case TYPE_SURCOAT:
							if ( temp_sum > my_surcoat_sum ) {
								rob_flag = 1;
								my_item_sum = my_surcoat_sum;
							}
							break;
						case TYPE_WAIST:
							if ( temp_sum > my_waist_sum ) {
								rob_flag = 1;
								my_item_sum = my_waist_sum;
							}
							break;
						case TYPE_SHIELD:
							if ( temp_sum > my_shield_sum ) {
								rob_flag = 1;
								my_item_sum = my_shield_sum;
							}
							break;
						case TYPE_FINGER:
							if ( temp_sum > my_finger_sum ) {
								rob_flag = 1;
								my_item_sum = my_finger_sum;
							}
							break;
						case TYPE_HANDS:
							if ( temp_sum > my_hands_sum ) {
								rob_flag = 1;
								my_item_sum = my_hands_sum;
							}
							break;
						case TYPE_BOOTS:
							if ( temp_sum > my_boots_sum ) {
								rob_flag = 1;
								my_item_sum = my_boots_sum;
							}
							break;

					}
					if ( rob_flag ) {
						rob_item = target_item;
						target_item_sum = temp_sum;
						break;  // found the armor worth to rob, break the loop
					}
				}
				else if ( target_item_type == ITEM_TYPE_WEAPON
							&& target_item->query("skill_type") == my_weapon_skill
							&& !(target_item->query("flag") & TWO_HANDED)) {
					int temp_sum = get_prop_sum( target_item );
					if ( temp_sum > my_weapon_sum ) {
						rob_item = target_item;
						rob_flag = 1;
						my_item_sum = my_weapon_sum;
						target_item_sum = temp_sum;
						break;  // found the weapon worth to rob, break the loop
					}
				}
			}

				// all item check done
			if ( rob_flag ) {
				action_flag = 2; // will follow and kill
				if (JJ_MANMADE_NPCD->is_debug_item()) {
					JJ_MANMADE_NPCD->debug_msg( query("name") + " ���� " + target->query("name") + " ���ϵ� " +
					rob_item->query("name") + " �ܲ���" );
					JJ_MANMADE_NPCD->debug_msg( "my_item_sum: " + my_item_sum + "  target_item_sum:"
					                             + target_item_sum );
				}
			}
		}

		if ( JJ_MANMADE_NPCD->is_debug_meet() )
		    JJ_MANMADE_NPCD->debug_msg( me->query("name") + " action flag: " + action_flag + " can_fight: " +
		    can_fight() + " is_healthy: " + is_healthy() );

			// do not kill or fight human player
		if ( userp(target) )
			action_flag = 0;


	    switch( action_flag ) {
			case 0:
				command("look " + target->query("id") );break;
			case 1:  // ɱ
				if ( can_fight() == 0 )
				    break;
				if ( JJ_MANMADE_NPCD->is_debug_kill() ) {
					mymsg = "�� [" + environment(me)->query("short") + "] " + me->query("name") + " �� "
					+ target->query("name") + " ����ɱ��!!!";
				}
				if ( is_healthy() == 0 ) {
					if ( JJ_MANMADE_NPCD->is_debug_kill() ) {
						mymsg += ",���� " + me->query("name") + " �����Ӻ���̫����, ֻ������";
						JJ_MANMADE_NPCD->debug_msg( mymsg );
					}
					return;
				}
				JJ_MANMADE_NPCD->debug_msg( mymsg );
				command("kill " + target->query("id") );
				message_vision("$N��е�: $n " + RANK_D->query_self_rude(this_object())
				                    + "��Ϳ��㲻˳����! \n", this_object(), target );
				break;
			case 2:  // ׷ɱ
			    if ( can_fight() == 0 )
				    break;
				if ( JJ_MANMADE_NPCD->is_debug_kill() ) {
					mymsg = "�� [" + environment(me)->query("short") + "] "
					+ me->query("name") + " ����׷ɱ "
					+ target->query("name") + " !!!";
				}
				if ( is_healthy() == 0 ) {
					if ( JJ_MANMADE_NPCD->is_debug_kill() ) {
						mymsg += ",���� " + me->query("name") + " �����Ӻ���̫����, ֻ������";
						JJ_MANMADE_NPCD->debug_msg( mymsg );
					}
					return;
				}
				JJ_MANMADE_NPCD->debug_msg( mymsg );
				if (rob_flag)
					message_vision("$N��Ц��: $n " + RANK_D->query_self_rude(this_object())
				                    + "��������ɱ��, ˭������� " + rob_item->query("name")
				                    + "?��������ֻ��ɱ��ȡ��,����㵹ù!" + "\n", this_object(), target );
				else
					message_vision("$N��е�: $n " + RANK_D->query_self_rude(this_object())
				                    + "��Ϳ��㲻˳����! ���첻ɱ���Ĳ�����!\n", this_object(), target );

				set_leader(target);
				command("kill " + target->query("id") );
				break;
			case 3:
				if ( can_fight() == 0 )
					break;
				if ( JJ_MANMADE_NPCD->is_debug_fight() ) {
					mymsg = "�� [" + environment(me)->query("short") + "] "
						+ me->query("name") + " ������ " + target->query("name") + " �ֽ��书";
				}
				if ( is_healthy() == 0 ) {
					if ( JJ_MANMADE_NPCD->is_debug_fight() ) {
						mymsg += ",���� " + me->query("name") + " �����Ӻ���̫����, ֻ������";
						JJ_MANMADE_NPCD->debug_msg( mymsg );
					}
					return;
				}
				JJ_MANMADE_NPCD->debug_msg( mymsg );
				message_vision("$N ����� $n �ֽ��书\n", this_object(), target );
				command("fight " + target->query("id") );
				break;
	}
}

void dummy_action() {
}
