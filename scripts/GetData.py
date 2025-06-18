import yfinance as yf

# Choose your symbol and date range
symbol = "SPY"
start_date = "2023-01-01"
end_date = "2023-06-01"
interval = "15m"  # could also be "1d", "1h", etc.

# Download data
df = yf.download(symbol, start=start_date, end=end_date, interval=interval)

# Save to CSV
df.to_csv("data/spy_15min.csv")

print("✅ Data saved to data/spy_15min.csv")
