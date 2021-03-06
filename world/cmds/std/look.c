// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */

// look.c
// "per" parts modified by none at 96/10/02

#include <room.h>
#include <ansi.h>
#include <armor.h>  // emotion
#include <weapon.h> // emotion

#define MODULED "/u/yekai/zbtz/moduled.c"
inherit F_CLEAN_UP;

int look_room(object me, object env);
int look_item(object me, object obj);
int look_living(object me, object obj);
int look_room_item(object me, string arg);

mixed *tianfu = ({
			({"str","体    格"}),
			({"con","根    骨"}),
			({"spi","灵    性"}),
			({"kar","福    缘"}),
			({"cps","定    力"}),
			({"cor","胆    识"}),
			({"per","容    貌"}),
			({"int","悟    性"}),
		 });

mapping family=(["方寸山三星洞":1,
                 "蜀山派":1,
				 "水月宫":1,
				 "南海普陀山":1,
                 "五庄观":1,
                 "阎罗地府":-1,
                 "月宫":1,
                 "东海龙宫":1,
                 "大雪山":-1,
                 "陷空山无底洞":-1,
                 "盘丝洞":-1,
                 "将军府":1,
                 "三界散仙":-1,
                 "昆仑山玉虚洞":1,
                 "火云洞":-1,
]);

string *per_msg_male1 = ({
HIY "举动如行云游水，独蕴风情，吸引所有异性目光。\n" NOR,
HIY "双目如星，眉梢传情，所见者无不为之心动。\n" NOR,
HIR "粉面朱唇，身姿俊俏，举止风流无限。\n" NOR,
HIR "丰神如玉，目似朗星，令人过目难忘。 \n" NOR,
MAG "面如美玉，粉妆玉琢，俊美不凡。\n" NOR,
 MAG "飘逸出尘，潇洒绝伦。\n" NOR,
        CYN "长得伟岸英挺，顾盼之间，神采飞扬。\n" NOR,
        CYN "丰姿英伟，气宇轩昂，确实是人中龙凤。\n" NOR,

});

string *per_msg_male2 = ({
        CYN "英俊潇洒，风度翩翩。\n" NOR,
        CYN "相貌出众，面目俊朗。\n" NOR,
        CYN "面貌清奇，丰姿非俗。\n" NOR,
YEL "腰圆背厚，面阔口方，骨格不凡。\n" NOR,
RED "眉目清秀，端正大方，一表人才。\n" NOR,
RED "双眼光华莹润，透出摄人心魄的光芒。\n" NOR,
});
string *per_msg_male3 = ({
        CYN "相貌平平，没什么好看的。\n" NOR,
        CYN "相貌凶恶，满脸横肉。\n" NOR,
        CYN "暴睛环眼，嘴脸凶顽。\n" NOR,
HIB "贼眉鼠眼，身高三尺，宛若猴状。 \n" NOR,
HIB "肥头大耳，腹圆如鼓，手脚短粗，令人发笑。 \n" NOR,
NOR "面颊凹陷，瘦骨伶仃，可怜可叹。 \n" NOR,
});
string *per_msg_male4 = ({
        CYN "长得一副姥姥不疼，舅舅不爱的模样。\n" NOR,
        CYN "长得蔫蔫的，一副无精打采的模样。 \n" NOR,
        CYN "五短三粗，肥头大耳，大概是猪八戒的本家。 \n" NOR,
BLU "眉歪眼斜，瘌头癣脚，不象人样。 \n" NOR,
BLU "呲牙咧嘴，黑如锅底，奇丑无比。 \n" NOR,
BLU "面如桔皮，头肿如猪，让人不想再看第二眼。 \n" NOR,
});
string *per_msg_female1 = ({
        CYN "长发如云，肌肤胜雪，不知倾倒了多少英雄豪杰。 \n" NOR,
        CYN "俏脸生春，妙目含情，轻轻一笑，不觉让人怦然心动。 \n" NOR,
        CYN "风情万种，楚楚动人，当真是我见犹怜。 \n" NOR,
MAG "气质美如兰，才华馥比山，令人见之忘俗。 \n" NOR,
HIM "灿若明霞，宝润如玉，恍如神妃仙子。 \n" NOR,
HIM "美若天仙，不沾一丝烟尘。 \n" NOR,
HIM "宛如"+HIW+"玉雕冰塑"+HIM+"，似梦似幻，已不再是凡间人物。 \n" NOR,

});
string *per_msg_female2 = ({
        CYN "婷婷玉立，容色秀丽，风姿动人。 \n" NOR,
        CYN "玉面娇容花含露，纤足细腰柳带烟。 \n" NOR,
        CYN "面带晕红，眼含秋波。举手投足之间，确有一番风韵。 \n" NOR,
RED "肌肤微丰，雅淡温宛，清新可人。 \n" NOR,
RED "鲜艳妍媚，肌肤莹透，引人遐思。 \n" NOR,
HIR "娇小玲珑，宛如飞燕再世，楚楚动人。 \n" NOR,
HIR "腮凝新荔，肌肤胜雪，目若秋水。 \n" NOR,
HIW "粉嫩白至，如芍药笼烟，雾里看花。 \n" NOR,
});
string *per_msg_female3 = ({
        CYN "虽算不上绝世佳人，也颇有几份姿色。 \n" NOR,
        CYN "长得还不错，颇有几份姿色。  \n" NOR,
YEL "虽不标致，倒也白净，有些动人之处。\n" NOR,
});
string *per_msg_female4 = ({
        CYN "长得比较难看。 \n" NOR,
        CYN "长得………唉！  \n" NOR,
BLU "丑如无盐，状如夜叉。\n" NOR,
BLU "歪鼻斜眼，脸色灰败，直如鬼怪一般。\n" NOR,
BLU "八字眉，三角眼，鸡皮黄发，让人一见就想吐。\n" NOR,
HIB "眼小如豆，眉毛稀疏，手如猴爪，不成人样。\n" NOR,
HIB "一嘴大暴牙，让人一看就没好感。\n" NOR,
NOR "满脸疙瘩，皮色粗黑，丑陋不堪。\n" NOR,
NOR "干黄枯瘦，脸色腊黄，毫无女人味。\n" NOR,

});

string *per_msg_kid1 = ({
        CYN "月眉星眼，灵气十足。\n" NOR,
        CYN "机灵活泼，神态非凡。\n" NOR,
        CYN "面若秋月，色如晓花。\n" NOR,
});

string *per_msg_kid2 = ({
        CYN "隆额大眼，脸色红润。\n" NOR,
        CYN "胖胖嘟嘟，逗人喜欢。\n" NOR,
        CYN "细皮嫩肉，口齿伶俐。\n" NOR,
});

string *per_msg_kid3 = ({
        CYN "身材矬矮，傻里傻气。\n" NOR,
        CYN "肥肥胖胖，小鼻小眼。\n" NOR,
        CYN "呆头呆脑，笨手笨脚。\n" NOR,
});

string *per_msg_kid4 = ({
        CYN "蓬头垢脚，脸黄肌瘦。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

string *pos_msg_yao1 = ({
        HIB "脸上隐隐泛出一股煞气。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

string *pos_msg_yao2 = ({
        HIB "身上围绕着一阵黑雾。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

string *pos_msg_yao3 = ({
        HIB "身上围绕着一团黑云。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

string *pos_msg_yao4 = ({
        HIB "整个笼罩在一团妖气之中。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

string *pos_msg_yao5 = ({
        HIB "好似夹带着无穷无尽的令人恐惧的力量, 吓得你想转身就逃走, 可是双腿已经不听你使唤了。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

string *pos_msg_xian1 = ({
        HIY "脸上显出一股祥和之气。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

string *pos_msg_xian2 = ({
        HIY "身上围绕着一团瑞气。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

string *pos_msg_xian3 = ({
        HIY "身边围绕着一朵祥云。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

string *pos_msg_xian4 = ({
        HIY "整个笼罩在"HIW"七"HIR"彩"HIM"祥"HIC"云"HIY"之中。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

// emotion begins
string *pos_msg_xian5 = ({
        HIY "身上发出金光万道, 令人感动得禁不住想要拜倒在地。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});
// emotion ends

// snowcat 12/20/97
string ride_suffix (object me)
{
  string ridemsg = 0;
  object ridee = 0;

  ridee = me->ride();
  if (ridee)
    ridemsg = ridee->query("ride/msg")+"在"+ridee->name()+"上";
  return ridemsg;
}

void create() { seteuid(getuid()); }
int main(object me, string arg)
{
   object obj;
   int result;

   if( !arg ) result = look_room(me, environment(me));
   else if( (obj = present(arg, me)) || (obj = present(arg, environment(me)))) {
     if( obj->is_character() ) result = look_living(me, obj);
     else result = look_item(me, obj);
   } else result = look_room_item(me, arg);

   return result;
}

int look_room(object me, object env)
{
   int i;
   object *inv;
   mapping exits;
   string str, str1="", *dirs;
   string ridemsg = "";

   if( !env ) {
     write("你的四周灰蒙蒙地一片，什么也没有。\n");
     return 1;
   }
   str = env->query("short")?(env->query("outdoors")?HIR"「"HIG+(string)env->query("short")+HIR"」"NOR:HIR"「"HIY+(string)env->query("short")+HIR"」"NOR): "";
   if ( wizardp(me) )// || me->query("env/show_path") )
       str += HIW+" - "+file_name(env)+NOR;
   str += "\n    " + (env->query("long")? env->query("long"): "\n") + (env->query("outdoors")? NATURE_D->outdoor_room_description() : "" );
   if( mapp(exits = env->query("exits")) ) {
     dirs = keys(exits);
     for(i=0; i<sizeof(dirs); i++)
        if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
          dirs[i] = 0;
     dirs -= ({ 0 });
     if( sizeof(dirs)==0 )
        str += "    这里没有任何明显的出路。\n";
     else if( sizeof(dirs)==1 )
        str += "    这里唯一的出口是 " + BOLD + dirs[0] + NOR + "。\n";
     else
        str += sprintf("    这里明显的出口是 " + BOLD + "%s" + NOR + " 和 " + BOLD + "%s" + NOR + "。\n",
          implode(dirs[0..sizeof(dirs)-2], "、"), dirs[sizeof(dirs)-1]);
     for (i = 0; i < sizeof(dirs); i++) {
		 if ( i % 2 == 0 )
		 	str += sprintf("\t"BOLD"%-20s"NOR, "(" + dirs[i] + ")" + exits[dirs[i]]->query("short"));
		 else
		 	str += sprintf("\t"BOLD"%s\n"NOR, "(" + dirs[i] + ")" + exits[dirs[i]]->query("short"));
	 }
	 if (i % 2 == 1)
	 	str += "\n";
   }
//   str += env->door_description();

   inv = all_inventory(env);
   i=sizeof(inv);
   while(i--) {
	 string temp;
     if( !me->visible(inv[i]) ) continue;
     if( inv[i]==me ) continue;

     temp = "  " + inv[i]->short();
     if ( wizardp(me) || me->query("env/show_file_name") )
     	temp = temp + "-" + file_name(inv[i]);
     if (ridemsg = ride_suffix(inv[i]))
        str1 = temp + " <"+ridemsg +
          ">\n"+str1;
     else
        str1 = temp + "\n"+str1;
   }

   write(str+str1);
   return 1;
}

int look_item(object me, object obj)
{
   mixed *inv;
//   write(obj->long());
   // begins -- emotion
   string desc, armor_type, weapon_type, special_effects;
   mapping armor_prop, weapon_prop;
   mixed *props;
   int i, weapon_flag, temp_value;
   desc = obj->query("name");
   if ( wizardp(this_player()) || this_player()->query("env/show_file_name"))
   		desc += " - " + file_name(obj) + "\n";
   else
   		desc += "\n";
   desc += "\n" + obj->long() + "\n";
   desc += "价值(" + ( obj->query("value") ? obj->query("value") : obj->value() ) + ")";
   desc += " 重量(" + obj->weight() + ")";
   if ( obj->is_newitem() ) {
	   desc += "\n============================================\n";
	   if (obj->is_armor() || obj->is_weapon() || obj->is_acc() ) {
		   desc += sprintf("当前等级: %6d        最高等级: %6d\n", obj->query("level"), obj->query("max_level"));
		   desc += "升级准备: ";
		   if (obj->query("level") >= obj->query("max_level")) {
			   desc += "------";
		   } else {
		   		desc += sprintf("%5d%%", obj->fight_exp_rate() );
		   }
		   if (obj->is_weapon()) {
			   desc += sprintf("        熟练程度: %5d%%", obj->op_exp_rate() );
		   }
		   if( !obj->is_acc() )
		   		desc += sprintf("\n镶有钻石: %6d        最多可镶: %6d", obj->query("sockets/now"), obj->query("sockets/max"));
		   if (obj->query("embed_msg"))
		   		desc += "\n镶有: " + obj->query("embed_msg") + "\n";
		   if (obj->is_weapon()) {
		   		desc += sprintf("\n物理伤害: %6d\n", obj->query("weapon_prop/damage"));
		   		desc += "五行伤害: ";
		   		if (obj->query("weapon_prop/gold_attack"))
		   			desc += HIY"金"NOR"<" + obj->query("weapon_prop/gold_attack") + ">";
		   		if (obj->query("weapon_prop/wood_attack"))
		   			desc += HIG"木"NOR"<" + obj->query("weapon_prop/wood_attack") + ">";
		   		if (obj->query("weapon_prop/water_attack"))
		   			desc += HIB"水"NOR"<" + obj->query("weapon_prop/water_attack") + ">";
		   		if (obj->query("weapon_prop/fire_attack"))
		   			desc += HIR"火"NOR"<" + obj->query("weapon_prop/fire_attack") + ">";
		   		if (obj->query("weapon_prop/earth_attack"))
		   			desc += YELGRN"土"NOR"<" + obj->query("weapon_prop/earth_attack") + ">";
		   		desc += "\n";
			}
		   	else {
		   		desc += sprintf("\n物理防御: %6d\n", obj->query("armor_prop/armor"));
		   		desc += "五行防御: ";
		   		if (obj->query("armor_prop/gold_defense"))
		   			desc += HIY"金"NOR"<" + obj->query("armor_prop/gold_defense") + ">";
		   		if (obj->query("armor_prop/wood_defense"))
		   			desc += HIG"木"NOR"<" + obj->query("armor_prop/wood_defense") + ">";
		   		if (obj->query("armor_prop/water_defense"))
		   			desc += HIB"水"NOR"<" + obj->query("armor_prop/water_defense") + ">";
		   		if (obj->query("armor_prop/fire_defense"))
		   			desc += HIR"火"NOR"<" + obj->query("armor_prop/fire_defense") + ">";
		   		if (obj->query("armor_prop/earth_defense"))
		   			desc += YELGRN"土"NOR"<" + obj->query("armor_prop/earth_defense") + ">";
		   		desc += "\n";
			}

	   } else {
		   		desc += "五行属性: ";
		   		if (obj->query("effect/gold"))
		   			desc += HIY"金"NOR"<" + obj->query("effect/gold") + ">";
		   		if (obj->query("effect/wood"))
		   			desc += HIG"木"NOR"<" + obj->query("effect/wood") + ">";
		   		if (obj->query("effect/water"))
		   			desc += HIB"水"NOR"<" + obj->query("effect/water") + ">";
		   		if (obj->query("effect/fire"))
		   			desc += HIR"火"NOR"<" + obj->query("effect/fire") + ">";
		   		if (obj->query("effect/earth"))
		   			desc += YELGRN"土"NOR"<" + obj->query("effect/earth") + ">";
		   		desc += "\n";
	   }
	   if( obj->query("wield/daoxing") )
	   {
		   desc += "装备要求：\n";
		   desc += "道    行：" + chinese_number(obj->query("wield/daoxing")) + "年\n";
		   /*desc += "道    行：" + chinese_number(obj->query("wield/daoxing")) + "年        ";
		   for(i=0;i<sizeof(tianfu);i++)
		   {
		   	if( obj->query("wield/"+tianfu[i][0]) > 0 )
		   		desc += tianfu[i][1] + "："+obj->query("wield/"+tianfu[i][0]);
		   }
		   desc += "\n";*/
	   }
	   desc += "============================================\n";
	   if (obj->query("mod"))
			desc += MODULED->print_mod(obj,me);
	   me->start_more(desc);
   } else {
	   if ( mapp(armor_prop = obj->query("armor_prop") ) && armor_type = obj->query("armor_type") ) {
		   desc += "  护具装备部位(";
		   switch (armor_type) {
			   case TYPE_HEAD:
				   desc += "头";
				   break;
			   case TYPE_NECK:
				   desc += "颈";
				   break;
			   case TYPE_CLOTH:
				   desc += "身";
				   break;
			   case TYPE_ARMOR:
				   desc += "盔甲";
				   break;
			   case TYPE_SURCOAT:
				   desc += "外套";
				   break;
			   case TYPE_WAIST:
				   desc += "腰";
				   break;
			   case TYPE_WRISTS:
				   desc += "腕";
				   break;
			   case TYPE_SHIELD:
				   desc += "盾";
				   break;
			   case TYPE_FINGER:
				   desc += "手指";
				   break;
			   case TYPE_HANDS:
				   desc += "手";
				   break;
			   case TYPE_BOOTS:
				   desc += "足";
				   break;
			   case "bandage":
				   desc += "伤口";
				   break;
			   default:
				   desc += "奇怪，居然不知道(" + armor_type + ")";
		   }
		   desc += ") 效果(";
		   props = keys( armor_prop );
		   for ( i = 0; i < sizeof( props ); i++ ) {
			   desc += " " + props[ i ] + "(" + armor_prop[ props[ i ] ] + ")";
		   }
		   desc += " )";
	   }

		  if ( mapp(weapon_prop = obj->query("weapon_prop") ) ) {
			  weapon_flag = obj->query("flag");
			  desc += "  武器特征(";
			  if ( weapon_flag & TWO_HANDED ) {
				  desc += " 双手";
			  }
			  if ( weapon_flag & SECONDARY ) {
				  desc += " 可用作第二武器";
			  }
			  if ( weapon_flag & EDGED ) {
				  desc += " 有刀刃的";
			  }
			  if ( weapon_flag & POINTED ) {
				  desc += " 尖的";
			  }
			  if ( weapon_flag & LONG ) {
				  desc += "长兵器";
			  }
			  desc += " )";

			  desc += " 技能(" + obj->query("skill_type") + ")";

		   desc += " 效果(";
		   props = keys( weapon_prop );
		   for ( i = 0; i < sizeof( props ); i++ ) {
			   desc += " " + props[ i ] + "<" + weapon_prop[ props[ i ] ] + ">";
		   }
		   desc += " )";
	   }

	   desc += " 特殊效果(";
	   if ( special_effects = obj->query("special_effects") ) {
		   desc += special_effects;
	   } else {
		   desc += "还未提供说明";
	   }
	   desc += ")";
	   if (obj->query("rzr_victim_num"))
			desc += "\n" + HIR"被人造人们用" + obj->query("rzr_victim_num") + "名受害者的鲜血祭过"NOR;
	   //  ends -- emotion
	   me->start_more(desc);
	   inv = all_inventory(obj);
	   if( sizeof(inv) ) {
		 inv = map_array(inv, "inventory_look", this_object() );
		 message("vision", sprintf("里面有：\n  %s\n",
			implode(inv, "\n  ") ), me);
	   }
   }
   return 1;
}
string pos_status_msg(int position)
{
  // beeby 7/14/2000
  if (position == 0) {  // emotion
	  return "看不出是妖还是仙";  // emotion
  } else if (position>0)
  {
     if (position<1000)  // emotion
	return (pos_msg_xian1[0]);
     else if (position<100000)  // emotion
         return (pos_msg_xian2[0]);
     else if (position<1000000)  // emotion
        return (pos_msg_xian3[0]);
     else if (position < 3456000 ) // emotion
        return (pos_msg_xian4[0]);
     else
        return (pos_msg_xian5[0]);
  } else
    {
     if (position>-1000) // emotion
        return (pos_msg_yao1[0]);
     else if (position>-100000)  // emotion
         return (pos_msg_yao2[0]);
     else if (position>-1000000)  // emotion
        return (pos_msg_yao3[0]);
     else if (position>-3456000) // emotion
        return (pos_msg_yao4[0]);
     else
        return (pos_msg_yao5[0]);
    }
}
string per_status_msg(int age, int per, string gender)
{
   // added by snowcat
   if (age < 14) {
     if ( per>=25 )
        return ( per_msg_kid1[random(sizeof(per_msg_kid1))]);
     else if ( per>=20 )
        return ( per_msg_kid2[random(sizeof(per_msg_kid2))]);
     else if ( per>=15 )
        return ( per_msg_kid3[random(sizeof(per_msg_kid3))]);
     else    return ( per_msg_kid4[random(sizeof(per_msg_kid4))]);
     }

   if ( gender == "男性" ) {
     if ( per>=25 )
        return ( per_msg_male1[random(sizeof(per_msg_male1))]);
     else if ( per>=20 )
        return ( per_msg_male2[random(sizeof(per_msg_male2))]);
     else if ( per>=15 )
        return ( per_msg_male3[random(sizeof(per_msg_male3))]);
     else    return ( per_msg_male4[random(sizeof(per_msg_male4))]);
     }

   if ( gender == "女性" ) {
     if ( per>=25 )
                        return ( per_msg_female1[random(sizeof(per_msg_female1))]);
                else if ( per>=20 )
                        return ( per_msg_female2[random(sizeof(per_msg_female2))
]);
                else if ( per>=15 )
                        return ( per_msg_female3[random(sizeof(per_msg_female3))
]);
         else   return ( per_msg_female4[random(sizeof(per_msg_female4))]);
                }
   else return "";
//   else return "长得怎样你没什么概念。\n";
}

int look_living(object me, object obj)
{
   string str, limb_status, ridemsg, pro;
   mixed *inv;
   mapping my_fam, fam;
// added for bian by mon.
        mapping ofamily;
   string ogender,orace;
   int oage;

   if(obj->query_temp("d_mana")>0) {
     ofamily=obj->query_temp("family");
     ogender=obj->query_temp("gender");
     orace=obj->query_temp("race");
     oage=obj->query_temp("age");
        } else {
     ofamily=obj->query("family");
     ogender=obj->query("gender");
     orace=obj->query("race");
     oage=obj->query("age");
//fake_age is set as the age when player gets dao-xing:不堕轮回。
//so later on, he/she always looks like the age of that time:)
//but need a "look" to activate all the relatived settings...weiqi
//only when one is not in the status of "bian", check his/her
//fake_age. mon 9/4/97
     if(obj->query("always_young") ) {
        if(oage>obj->query("fake_age")) {
        //if "age" is less than fake_age, reset fake_age.
        //mon 9/4/97
     oage=obj->query("fake_age");
             } else {
               obj->set("fake_age", oage);
        }
     }
     else{
     if(obj->query("combat_exp") > 729000){
obj->set("always_young", 1);
obj->set("fake_age", oage);
     }
     }
//done with fake_age.
        }


   if( me!=obj && obj->visible(me) )
     message("vision", me->name() + "正盯着你看，不知道打些什么主意。\n", obj);

   str = obj->long();

   str = replace_string(str, "$n", me->name());
   str = replace_string(str, "$N", obj->name());
    str = replace_string(str, "$C", RANK_D->query_respect(obj));
    str = replace_string(str, "$c", RANK_D->query_rude(obj));
   str = replace_string(str, "$R", RANK_D->query_respect(me));
   str = replace_string(str, "$r", RANK_D->query_rude(me));


   pro = (obj==me) ? gender_self(ogender) : gender_pronoun(ogender);

        if(obj->query_temp("d_mana")==0 || obj->query_temp("is_character")) {

   if( orace=="人类"
   &&   intp(oage) )
     if(oage<10) {
        str += sprintf("%s看起来显然还不到十岁。\n", pro);
     }
     else{
        str += sprintf("%s看起来约%s多岁。\n", pro, chinese_number(oage / 10 * 10));
     }

   //check about wife and husband
   if((obj->parse_command_id_list())[0]==me->query("couple/id") ) {
     if( (string)me->query("gender")=="女性" ){
     str += sprintf("%s是你的丈夫。\n", pro);
     }
     else{
        str += sprintf("%s是你的妻子。\n", pro);
     }
   }
   // If we both has family, check if we have any relations.
   if( obj!=me
   &&   mapp(fam = ofamily)
   &&   mapp(my_fam = me->query("family"))
   &&   fam["family_name"] == my_fam["family_name"] ) {

     if( fam["generation"]==my_fam["generation"] ) {
        if( ogender == "男性" )
          str += sprintf( pro + "是你的%s%s。\n",
             my_fam["master_id"] == fam["master_id"] ? "": "同门",
             my_fam["enter_time"] > fam["enter_time"] ? "师兄": "师弟");
        else
          str += sprintf( pro + "是你的%s%s。\n",
             my_fam["master_id"] == fam["master_id"] ? "": "同门",
             my_fam["enter_time"] > fam["enter_time"] ? "师姐": "师妹");
     } else if( fam["generation"] < my_fam["generation"] ) {
        if( member_array(my_fam["master_id"],
            obj->parse_command_id_list())>-1  )
          str += pro + "是你的师父。\n";
        else if( my_fam["generation"] - fam["generation"] > 1 )
          str += pro + "是你的同门长辈。\n";
        else if( fam["enter_time"] < my_fam["enter_time"] )
          str += pro + "是你的师伯。\n";
        else
          str += pro + "是你的师叔。\n";
     } else {
        if( fam["generation"] - my_fam["generation"] > 1 )
          str += pro + "是你的同门晚辈。\n";
        else if( fam["master_id"] == me->query("id") )
          str += pro + "是你的弟子。\n";
        else
          str += pro + "是你的师侄。\n";
     }
   }

/*   if( obj->query("max_kee") )
     str += pro + COMBAT_D->eff_status_msg((int)obj->query("eff_kee") * 100 / (int)obj->query("max_kee")) + "\n";
*/

//here, if per>=100, no rong-mao description, it'll be necessary sometimes.
//return special looking first if he/she has one.

   if( obj->query("looking") ){
     str += pro + (string)obj->query("looking") + "\n";
   } else {
     string looking= per_status_msg((int)obj->query("age"),
            (int)obj->query_per(), ogender);
              if( strlen(looking)>1 && obj->query("per") < 100 )
                    str += pro + looking;
   }

   ridemsg = ride_suffix(obj);
   if (ridemsg)
     str += pro + "正" + ridemsg + "。\n";

// Beeby 7/14/2000
// show position
//   str += pro + pos_status_msg(obj->query("position"))+"\n";
   str += pro; // emotion
   if (obj->query("yaoorxian")) // emotion
       str += pos_status_msg(obj->query("yaoorxian") * obj->query( "daoxing" ) )+"\n";  // emotion
   else
       str += pos_status_msg(family[obj->query("family/family_name")] * obj->query( "daoxing" ) )+"\n";  // emotion
   inv = all_inventory(obj);
   if( sizeof(inv) ) {
     inv = map_array(inv, "inventory_look", this_object(), obj->is_corpse()? 0 : 1 );
     inv -= ({ 0 });
     if( sizeof(inv) )
        str += sprintf( obj->is_corpse() ? "%s的遗物有：\n%s\n" : "%s身上带着：\n%s\n",          pro, implode(inv, "\n") );
   }

   }

        me->start_more(str);

   if( obj!=me
   &&   living(obj)
   &&   random((int)obj->query("bellicosity")/10) > (int)me->query_per() ) {
     write( obj->name() + "突然转过头来瞪你一眼。\n");
     COMBAT_D->auto_fight(obj, me, "berserk");
     return 1;
   }

//this part is  taken from attack.c
//mon 1/22/98
/*
   if( obj!=me
   && living(obj)
   && userp(obj)
        && random((int)obj->query("bellicosity")/40) > (int)obj->query("cps") )
     COMBAT_D->auto_fight(obj, me, "berserk");
*/

   return 1;
}

string inventory_look(object obj, int flag)
{
   string str;

   str = obj->short();
   if ( wizardp(this_player()) || this_player()->query("env/show_file_name"))
   		str += " - " + file_name(obj);
   if( obj->query("equipped") )
     str = HIC "  □" NOR + str;
   else if( !flag )
     str = "    " + str;
   else
     return 0;

   if (obj->is_newitem() && obj->query("newitem_owner_id"))
   		str += HIC"<已注册>"NOR;

   return str;
}

int look_room_item(object me, string arg)
{
   object env;
   mapping item, exits;

   if( !objectp(env = environment(me)) )
     return notify_fail("这里只有灰蒙蒙地一片，什么也没有。\n");

   if( mapp(item = env->query("item_desc")) && !undefinedp(item[arg]) ) {
     if( stringp(item[arg]) )
        write(item[arg]);
     else if( functionp(item[arg]) )
        write((string)(*item[arg])(me));

     return 1;
   }
   if( mapp(exits = env->query("exits")) && !undefinedp(exits[arg]) ) {
     if( objectp(env = load_object(exits[arg])) )
        look_room(me, env);
     else {
       return notify_fail("你什么也看不见。\n");
     }
     return 1;
   }
  return notify_fail("你要看什么？\n");
}

int help (object me)
{
   write(@HELP
指令格式: look [<物品>|<生物>|<方向>]

这个指令让你查看你所在的环境、某件物品、生物、或是方向。

HELP
);
   return 1;
}
