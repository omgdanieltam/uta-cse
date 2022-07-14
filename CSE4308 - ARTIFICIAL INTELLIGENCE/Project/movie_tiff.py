import pandas as pd
import numpy as np

def get_similar_movies(movie_name, user_rating):
  similar_score = item_similarity_df[movie_name] * (user_rating-2.5)
  similar_score = similar_score.sort_values(ascending = False)

  return similar_score

def get_user_list(user_ratings, id):
    user = list()

    ratings = list(user_ratings.iloc[id])
    titles = list(user_ratings)

    for i in range(0, len(ratings)):
        if ratings[i] != 0.0:
            for j in range(0, len(movie_list)):
              if titles[i] == movie_list[j]:
                final_ratings[j] = final_ratings[j] + ratings[i]

    return

user_list = input("Input user list separated by commas (ex: 2,32,76): ")

ratings = pd.read_csv('ratings.csv')
movies = pd.read_csv('movies.csv')
ratings = pd.merge(movies, ratings)

userratings = ratings.pivot_table(index = ['userId'], columns = ['title'], values = 'rating')

#to avoid noise, if a movie has less than 5 users who rates it then we will delete it.
#Also, fill NaN w/ 0
userratings = userratings.dropna(thresh=5, axis =1).fillna(0)

#build the similarity matrix
item_similarity_df = userratings.corr(method = 'pearson')

# setup
all_users = list()
movie_list = list(movies.iloc[:,1])
final_ratings = [0] * len(movie_list)
complete = list()

# convert users in list
user_list = user_list.split(',')
for i in range(0, len(user_list)):
  get_user_list(userratings, int(user_list[i])-1)

# Get the average of all the ratings
average_list = [i / len(user_list) for i in final_ratings]

# Conver to proper format
for i in range(0, len(movie_list)):
  if average_list[i] != 0:
    complete.append((movie_list[i], average_list[i]))

romance_lover = complete

similar_movies = pd.DataFrame()

for movie,rating in romance_lover:
  similar_movies = similar_movies.append(get_similar_movies(movie,rating), ignore_index = True)

romance_lover_movies = np.delete(romance_lover, 1, 1).flatten()
print(similar_movies.sum().sort_values(ascending = False).drop(labels=romance_lover_movies))
