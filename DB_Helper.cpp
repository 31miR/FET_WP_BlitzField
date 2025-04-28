#include "DB_Helper.h"

int DB_Helper::count_callback(void *value, int argc, char **argv, char **column_names)
{
  int *result = (int *)value;
  *result = std::atoi(*argv);
  return 0;
}
int DB_Helper::player_data_callback(void *value, int argc, char **argv, char **column_names)
{
  Player_Data *result = (Player_Data *)value;
  result->name = argv[0];
  result->health_upgrades = std::atoi(argv[1]);
  result->stamina_upgrades = std::atoi(argv[2]);
  result->unspent_upgrades = std::atoi(argv[3]);
  result->levels_finished_count = std::atoi(argv[4]);
  result->last_level_played = std::atoi(argv[5]);
  return 0;
}
int DB_Helper::string_vector_callback(void *value, int argc, char **argv, char **column_names)
{
  std::vector<std::string> *result = (std::vector<std::string> *)value;
  for (int i = 0; i < argc; ++i)
  {
    (*result).push_back(argv[i]);
  }
  return 0;
}

bool DB_Helper::is_username_in_DB(const std::string &username)
{
  sqlite3 *db;
  sqlite3_open("game_data.db", &db);
  std::string query = "SELECT COUNT(*) FROM Player_Data WHERE Player_Data.name = '";
  query += username + "';";
  int result;
  sqlite3_exec(db, query.c_str(), count_callback, &result, 0);
  sqlite3_close(db);
  return !(result == 0);
}
void DB_Helper::create_new_profile_in_DB(const std::string &username)
{
  if (is_username_in_DB(username))
    return;
  sqlite3 *db;
  sqlite3_open("game_data.db", &db);
  std::string query = "INSERT INTO "
                      "Player_Data(name, health_upgrades, stamina_upgrades, unspent_upgrades, levels_finished_count, last_level_played) VALUES('";
  query += username + "', 0, 0, 0, 0, -1;";
  sqlite3_exec(db, query.c_str(), 0, 0, 0);
  sqlite3_close(db);
}
void DB_Helper::update_profile_in_DB(const Player_Data &new_data)
{
  if (!is_username_in_DB(new_data.name))
    return;
  sqlite3 *db;
  sqlite3_open("game_data.db", &db);
  std::string query = "UPDATE Player_Data SET "
                      "health_upgrades = ";
  query += std::to_string(new_data.health_upgrades) + ", " +
           "stamina_upgrades = " + std::to_string(new_data.stamina_upgrades) + ", " +
           "unspent_upgrades = " + std::to_string(new_data.unspent_upgrades) + ", " +
           "levels_finished_count = " + std::to_string(new_data.levels_finished_count) + ", " +
           "last_level_played = " + std::to_string(new_data.last_level_played) + " " +
           "WHERE name = '" + new_data.name + "';";
  sqlite3_exec(db, query.c_str(), 0, 0, 0);
  sqlite3_close(db);
}
Player_Data DB_Helper::get_profile_from_username_in_DB(const std::string &username)
{
  sqlite3 *db;
  sqlite3_open("game_data.db", &db);
  std::string query = "SELECT * FROM Player_Data WHERE Player_Data.name = '";
  query += username + "';";
  Player_Data result;
  sqlite3_exec(db, query.c_str(), player_data_callback, &result, 0);
  sqlite3_close(db);
  return result;
}
std::vector<std::string> DB_Helper::get_all_profiles_in_DB()
{
  sqlite3 *db;
  sqlite3_open("game_data.db", &db);
  std::string query = "SELECT Player_Data.name FROM Player_Data;";
  std::vector<std::string> result;
  sqlite3_exec(db, query.c_str(), string_vector_callback, &result, 0);
  sqlite3_close(db);
  return result;
}
