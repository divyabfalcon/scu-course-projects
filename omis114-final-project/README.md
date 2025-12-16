# **Capstone Project: Sales Data Analysis and Customer Insights**

## **Overview**

This project provides a comprehensive data science analysis of a sales and customer dataset (sales\_data.csv). The primary goal is to establish data integrity, perform rigorous statistical analysis, implement an initial machine learning model to predict customer value, and derive actionable, data-driven business recommendations.

The analysis is documented step-by-step in the Jupyter Notebook Capstone\_Project (2).ipynb.

## Team Contributions

This capstone project was completed as a group with Ella Johnston and Tyler Singh.

- Tyler Singh: Sections 2 and 3 (Data Cleaning & Preprocessing; Statistical Analysis), and authored the initial project documentation files (requirements.txt and README.md), and the final presentation content for those components.
- Ella Johnston: Sections 1 and 4 (Data Loading & Exploration; Data Visualization), and the final presentation content for those components.
- Divya Bengali (me): Sections 5 and 6 (Machine Learning Implementation; Business Insights & Recommendations), the interactive dashboard (optional bonus), and the final presentation content for those components.

All team members contributed to the final presentation.


## **Key Findings (Summary from Analysis)**

The statistical and predictive modeling revealed critical insights into customer value and transaction predictability:

1. **High-Value Drivers are Tenure and Income:** The machine learning model identified **Customer Income** and **Customer Lifespan Days (tenure)** as the most critical features for predicting high-value customers.  
2. **Volatile Sales Range:** The 95% Prediction Interval for a single sale is **$0.00 to $494.04** (Mean: $187.35$). This high variability confirms that high-value transactions are inconsistent, requiring standardized, high-tier product offerings.  
3. **Gender Neutrality in Spending:** A Two-Sample T-Test confirmed **no statistically significant difference** in the mean transaction revenue between male and female customers, allowing marketing focus to shift to income and location.

## **Strategic Recommendations**

The derived recommendations are focused on increasing customer lifespan and formalizing high-value sales:

1. **Launch a '90-Day Lifespan Accelerator' Program** to lock in customer engagement early.  
2. **Introduce Income-Based 'Elite Bundles'** to target high-income customers and standardize high-tier revenue.  
3. **Align Inventory with High-Value Locations** (New York, Boston, San Francisco) to optimize fulfillment in high-yield areas.

## **Repository Structure**

.  
├── Capstone\_Project.ipynb \# Primary analysis notebook  
├── sales_data.csv             \# Raw data file  
└── README.md                  \# This file  
└── requirements.txt           \# Python dependencies

## **Setup and Execution**

To replicate the analysis, follow these steps:

1. **Clone the repository and ensure data file is present.**  
2. Install Dependencies:  
   Install the required Python libraries using the generated requirements.txt file:  
   pip install \-r requirements.txt

3. Run the Analysis:  
   Open the Capstone\_Project (2).ipynb file in a Jupyter environment and execute the cells sequentially. The notebook details data loading, cleaning (including the check for negative revenue), statistical tests, and preliminary ML implementation.


## Notes
Assignment prompts/instructions provided by the course were instructor-provided and are not included here. This repository contains student-created work only.
