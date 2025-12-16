import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt

#NOTE: THE IMAGE I HAD SET AS A LOGO WAS FOUND ON THE INTERNET ON THIS SITE: https://en.wikipedia.org/wiki/Santa_Clara_University
st.set_page_config(page_title="Sales Dashboard", page_icon ="Santa_Clara_U_Seal.svg.png", layout = "wide")

df=pd.read_csv("sales_data.csv")

if "transaction_revenue" not in df.columns:
    df["transaction_revenue"] = df["price"] * df["quantity"]

for col in ["product_category", "location", "gender"]:
    df[col] = df[col].fillna("Unknown").astype(str)

#Filters
st.sidebar.header("Filters")
categories = sorted(df["product_category"].unique())
selected_categories = st.sidebar.multiselect(
    "Product category",
    options = categories,
    default = categories
)

locations = sorted(df["location"].unique())
selected_locations = st.sidebar.multiselect(
    "Location",
    options = locations,
    default = locations
)

genders = sorted(df["gender"].unique())
selected_genders = st.sidebar.multiselect(
    "Gender",
    options = genders,
    default = genders
)


# "Applies" the filters here
filtered_df = df[
    df["product_category"].isin(selected_categories)
    & df["location"].isin(selected_locations)
    & df["gender"].isin(selected_genders)
].copy()

st.title("Sales Data Dashboard")

# Recalculates based on filtered data
total_revenue = filtered_df["transaction_revenue"].sum()
avg_order_value = filtered_df["transaction_revenue"].mean()
num_customers = filtered_df["customer_id"].nunique()
num_transactions = len(filtered_df)
                
col1, col2, col3, col4 = st.columns(4)
col1.metric("Total Revenue", f" ${total_revenue:,.2f}")
col2.metric("Avg order value", f" ${avg_order_value:,.2f}")
col3.metric("Unique customers", f" ${num_customers:,}")
col4.metric("Transactions", f" ${num_transactions:,}")

st.markdown("---")
st.subheader("Revenue by product category")
cat_rev = (
    filtered_df.groupby("product_category")["transaction_revenue"]
        .sum()
        .sort_values(ascending = False)
        .reset_index()
)

fig, ax = plt.subplots(figsize=(8,4))
ax.bar(cat_rev["product_category"], cat_rev["transaction_revenue"])
ax.set_xlabel("Product Category")
ax.set_ylabel("Total revenue")
ax.set_title("Total revenue by product category")
plt.xticks(rotation = 45, ha = "right")
st.pyplot(fig)

                